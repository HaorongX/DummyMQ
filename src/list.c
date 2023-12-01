#include "list.h"

struct blist *create_list() {
	struct blist *l = (struct blist *)malloc(sizeof(struct blist));
	l->head = l->end = NULL;
	return l;
}

struct lnode *append(struct blist *l, void *data) {
	struct lnode *n = (struct lnode *)malloc(sizeof(struct lnode));
	n->data = data;
	n->prev = l->end;
	n->next = NULL;

	if (l->head == NULL)
		l->head = l->end = n;
	else {
		l->end->next = n;
		l->end = n;
	}
	return n;
}
struct lnode *pop(struct blist *l) {
	struct lnode *t = l->end;
	if (l->head == l->end) {
		l->head = l->end = NULL;
		return t;
	}
	t->prev->next = NULL;
	l->end = t->prev;
	return t;
}
bool empty(const struct blist *l)
{
    return l->head == NULL;
}
void clean(struct blist *l)
{
    struct lnode *t = l->head, *s;
    for(; t; t = s)
    {
        s = t->next;
        free(t);
    }
}