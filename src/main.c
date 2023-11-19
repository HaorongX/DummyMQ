#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "socket_wrapped.h"
#include "type.h"

int setup_listenfd(uint16_t port);
 
int setup_listenfd(uint16_t port)
{
    int fd;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    fd = _socket(AF_INET, SOCK_STREAM, 0);
    _bind(fd, (struct sockaddr*)&serv_addr);
    _listen(fd, 10);
    return fd;
}

int
main(int argc, char **argv)
{
    int listenfd = setup_listenfd(8000), clientfd;

    struct bst str, tmp;
    char *data = NULL;
    while(true)
    {
        clientfd = _accept(listenfd, (struct sockaddr*) NULL, 0);
        
        read_bst(clientfd, &str);
        printf("%s\n", str.str);
        if(!strcmp(str.str, "PRO"))
        {
            free(data);
            data = str.str;
        }
        else if(!strcmp(str.str, "CON"))
        {
            if(data != NULL)
            {
                tmp.length = strlen(data);
                tmp.str = data;
                write_bst(clientfd, &tmp);
                free(data);
                data = NULL;
            }
            else 
            {
                tmp.length = strlen("NULL");
                tmp.str = "NULL";
                write_bst(clientfd, &tmp);
            }
        }
        else
        {
            printf("to a unknown client!\n");
        }
        close(clientfd);
    }
    free(data);
    return 0;
}