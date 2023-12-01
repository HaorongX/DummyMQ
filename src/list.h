#ifndef LIST_H
#define LIST_H

#include "type.h"

struct lnode {
	struct lnode *prev, *next;
	struct bst *data;
};

struct blist {
	struct lnode *head, *end;
};

struct blist *create_list();
struct lnode *append(struct blist *l, void *data);
struct lnode *pop(struct blist *l); // Please mind: IT'S ALWAYS YOUR DUTY TO RELEASE THE MEMORY USED BY THE NODE!
bool empty(const struct blist *l);
void clean(struct blist *l);

#endif