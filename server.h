#ifndef Server_h
#define Server_h

//#include <winsock.h>
#include <WinSock2.h>

struct Server {
    int domain;
    int service;
    int protocol;
    u_long _interface;
    int port;
    int backlog;

    struct sockaddr_in address;
    int socket;
    struct Sections *config_sections;
    void (*launch)(struct Server *server);
};

// params domain, service, protocol, _interface, port, backlog, pointer of function *luanch
struct Server server_constructor(int, u_long, void (*)(struct Server *server));
void initialize_from_file(int*, int*, int*, int*);
void load_essential_param(struct Server *server, const char *config);
#endif 
