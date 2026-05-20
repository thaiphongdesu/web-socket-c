#include "server.h"
#include <stdio.h>
#include "utils.h"
#include <stdbool.h>

void launch(struct Server *server);
struct Sections *test_parse_sections();
void debug_in_ascii(char *buffer);
void test_find_section_name(const char *section_name, struct Sections *sections);

int main() {
    struct Server server = server_constructor(AF_INET, INADDR_ANY, launch);
    server.launch(&server);
    // char section_name[256] = "SERVER_CONFIG";
    // struct Section *section = read_section(section_name);
    // if(section) {
    //     printf("Section SERVER_CONFIG is found\n");
    // } else if(section == NULL) printf("Section SERVER_CONFIG is not found\n");
    // struct Sections *sections = test_parse_sections();
    // test_find_section_name("Server_config", sections);
    de_allocate_list(server.config_sections->list);
    free(server.config_sections);
    return 0;
}

void launch(struct Server *server) {
    char buffer[1024];
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 48\n\n<html><body><h1>Hello, World!</h1></body></html>";
    char *greeting = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 78\n\n<html><body><h1>Greeeting stranges!\n Welcome to my website!</h1></body></html>";
    printf("===== WAITING FOR CONNECTION =====\n");
    int address_len = sizeof(server->address);
    int new_socket = accept(server->socket, (struct sockaddr*)&server->address, &address_len);
    while(1) {
        recv(new_socket, buffer, 1024, 0);
        printf("%s\n", buffer);
        char hello_tag[11];
        snprintf(hello_tag, 11, "%s", buffer);
        printf("hello tag: %s\n", hello_tag);
        if(strncmp(hello_tag, "GET /hello", 11) == 0) {
            printf("received hello tag\n");
            send(new_socket, greeting, strlen(greeting), 0);
        } else {
            // basic case
            send(new_socket, hello, strlen(hello), 0);
        }
    }
    WSACleanup();
    closesocket(new_socket);
}

struct Sections *test_parse_sections() {
    struct Sections *sections = parse_sections();
    struct Singly *temp = sections->list;
    while(temp) {
        printf("Section name: %s\n", temp->list_name);
        struct Node *item = temp->begin;
        while(item) {
            printf("%s\n", item->data);
            item = item->next;
        }
        temp = temp->next;
    }
    return sections;
}

void test_find_section_name(const char *section_name, struct Sections *sections) {
    struct Singly *section = find_section(section_name, sections);
    int service, protocol, port, backlog;
    if(sections) {
        printf("test_find_section_name debug - section_name in object: %s\n", section->list_name);
        initialize_from_parsed_section(section, &service, &protocol, &port, &backlog);
        printf("test_find_section_name debug - values: %d %d %d %d\n", service, protocol, port, backlog);
    }
}

void debug_in_ascii(char *buffer) {
    char c = buffer[0];
    unsigned int i = 0;
    while(c !=  '\0') {
        printf("%d ", c);
        c = buffer[++i];
    }
}