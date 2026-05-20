#include "server.h"
#include <stdio.h>
#include <string.h>

#include "utils.h"

#define SERVER_CONFIG "SERVER_CONFIG"

struct Server server_constructor(int domain, /*int service, int protocol,*/ u_long _interface,/* int port, int backlog, */void(*launch)(struct Server *server)) {
    WSADATA wsa;
    
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Lỗi khởi tạo Winsock. Mã lỗi: %d\n", WSAGetLastError());
        exit(1);
    }    

    struct Server server;
    struct Sections *sections = parse_sections();
    server.config_sections = sections;

    // service | protocol | port | backlog will be loaded from file setting
    load_essential_param(&server, SERVER_CONFIG);
    server.domain       = domain;
    server._interface   = _interface;
    server.launch        = launch;

    server.address.sin_family           = domain;
    server.address.sin_port             = htons(server.port);
    server.address.sin_addr.s_addr      = htonl(_interface);
    
    /* service SOCK_STREAM ==  TCP | SOCK_DGRAM == UDP
       protocol IPPROTO_TCP = 6 or IPPROTO_UDP = 17, 0 is
       shorthand for use the usual one                 */
    server.socket = socket(server.domain, server.service, server.protocol);   
    if(server.socket == 0) {
        printf("Failed to connect socket. Error: %d\n", WSAGetLastError());
        exit(1);
    }    

    if((bind(server.socket, (struct sockaddr*)&server.address, sizeof(server.address))) < 0) {
        printf("Failed to bind socket. Error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }    

    if(listen(server.socket, server.backlog) < 0) {
        printf("Failed to start listening. Error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }    

    return server;
}

void load_essential_param(struct Server *server, const char *config) {
    struct Singly *section = find_section(config, server->config_sections);
    if(section) {
        initialize_from_parsed_section(section, &server->service, &server->protocol, &server->port, &server->backlog);
        printf("load_essential_param debug - values: %d %d %d %d\n", server->service, server->protocol, server->port, server->backlog);
    } else {
        printf("Can not found section with config name: %s in file: %s\n", config, file_name);
    }
}

