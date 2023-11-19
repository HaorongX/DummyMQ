#ifndef TYPE_H
#define TYPE_H

#include "socket_wrapped.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/*
Basic string type
*/
struct bst
{
    size_t       length; //length of the string
    char        *str;    // data
};

void read_bst(int fd, struct bst *s);
void write_bst(int fd, const struct bst *s);

#endif