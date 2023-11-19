#include "type.h"
#include <stdlib.h>

// Who use this function should free the string  in s
void read_bst(int fd, struct bst *s)
{
    memset(s, 0, sizeof(struct bst));
    if(fd < 0)
        err_sys("Illegal fd!", __FILE__, __LINE__);

    if(read(fd, &s->length, sizeof(size_t)) < sizeof(size_t))
        err_sys("A error occurs during transfering a bst!", __FILE__, __LINE__);
    size_t c = s->length, d;
    char *buf = (char*)calloc(s->length, sizeof(char));
    s->str = (char*)calloc(s->length, sizeof(char)); // alloc & initialize
    while(d = read(fd, buf,c), d > 0 && c > 0)
    {
        c -= d;
        strcat(s->str, buf);
        memset(buf, 0, s->length * sizeof(char));
    }
    if(c > 0 || d < 0)
        err_sys("A error occurs during transfering a bst!", __FILE__, __LINE__);
    free(buf);
}

void write_bst(int fd, const struct bst *s)
{
    if(strlen(s->str) != s->length) 
        err_sys("The length given cannot match its actual length!", __FILE__, __LINE__);
    if(write(fd, &s->length, sizeof(s->length)) < 0)
        err_sys("A error occurs during transfering a bst!", __FILE__, __LINE__);
    size_t c = s->length, d;
    char *head = s->str;
    while(d = write(fd, head,c), d > 0 && c > 0)
    {
        c -= d;
        head += d;
    }
    if(c > 0 || d < 0)
        err_sys("A error occurs during transfering a bst!", __FILE__, __LINE__);
}