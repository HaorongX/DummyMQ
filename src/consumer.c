/*
THIS CONSUMER IS FOR TEST PURPOSE ONLY!!!
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "socket_wrapped.h" 
#include "type.h"

int
main(int argc, char **argv)
{
    int listenfd;
    struct sockaddr_in serv_addr;

    listenfd = _socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8000);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _connect(listenfd, (struct sockaddr*)&serv_addr);

    struct bst b={3,"CON"};

    write_bst(listenfd, &b);
    read_bst(listenfd, &b);
    printf("%s\n", b.str);
    return 0;
}