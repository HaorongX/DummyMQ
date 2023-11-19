#include "socket_wrapped.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int 
_socket(int domain, int type, int protocol)
{
    int fd = socket(domain,type,protocol);
    if(fd < 0)
        err_sys("Failed to create TCP socket.", NULL, 0);
    return fd;
}

void 
_listen(int fd, int n)
{
    if(listen(fd,n) < 0)
        err_sys("Failed to create listen socket!", NULL, 0);
}

int 
_accept(int fd, struct sockaddr *addr, socklen_t *addr_len)
{
    int f = accept(fd, addr, addr_len);
    if(f < 0)
        err_sys("Failed to create connect to the client", NULL, 0);
    return f;
}

void 
_bind(int fd, const struct sockaddr *addr)
{
    if(bind(fd, addr, sizeof(struct sockaddr)) < 0)
        err_sys("Failed to bind socket to the port!", NULL, 0);
}

void 
_connect(int fd, struct sockaddr *addr)
{
    if(connect(fd, addr, sizeof(*addr)) < 0)
        err_sys("Failed to build a connection!", NULL, 0);
}