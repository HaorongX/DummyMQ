#ifndef SOCKET_WRAPPED_H
#define SOCKET_WRAPPED_H

#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>

void 
err_sys(const char *err_msg, const char *file_name, const int line_no);

int 
_socket(const int domain, const int type, int protocol);

void 
_listen(int fd, int n);

int 
_accept(int fd, struct sockaddr *addr, socklen_t *addr_len);

void 
_bind(int fd, const struct sockaddr *addr);

void 
_connect(int fd, struct sockaddr *addr);

#endif