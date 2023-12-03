#include "list.h"
#include "socket_wrapped.h"
#include "type.h"
#include <semaphore.h>
#include <netdb.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct blist *queue;
sem_t mutex;

// TODO: need to make it irrelevant to proctocol(using getaddr)
int setup_listenfd(uint16_t port) {
	int fd;
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	fd = _socket(AF_INET, SOCK_STREAM, 0);
	_bind(fd, (struct sockaddr *)&serv_addr);
	_listen(fd, 10);
	return fd;
}

void serve_producer(int clientfd) {
	struct bst str;
	read_bst(clientfd, &str);
	sem_wait(&mutex);
	append(queue, (void *)str.str);
	sem_post(&mutex);
}

void serve_consumer(int clientfd) {
	struct bst tmp;
	if (!empty(queue)) {
		sem_wait(&mutex);
		struct lnode *n = pop(queue);
		sem_post(&mutex);
		tmp.length = strlen((char *)n->data);
		tmp.str = (char *)n->data;
		write_bst(clientfd, &tmp);
		free(n->data);
		free(n);
	} else {
		tmp.length = strlen("NULL");
		tmp.str = "NULL";
		write_bst(clientfd, &tmp);
	}
}

void *serve_client(void *vargp) {
	pthread_detach(pthread_self());
	int clientfd = *(int *)vargp;
	free(vargp);

	static char *data = NULL;
	struct bst str;

	read_bst(clientfd, &str);

	if (!strcmp(str.str, "PRO"))
		serve_producer(clientfd);
	else if (!strcmp(str.str, "CON"))
		serve_consumer(clientfd);
	else
		err_sys("Connected to a unknown client", __FILE__, __LINE__);

	close(clientfd);
	return NULL;
}

int main(int argc, char **argv) {
	int listenfd = setup_listenfd(8000);
	int *clientfd;
	pthread_t p;
	sem_init(&mutex, 0, 1);

	queue = create_list();
	while (true) {
		clientfd = (int *)malloc(sizeof(int));
		*clientfd = _accept(listenfd, (struct sockaddr *)NULL, 0);
		pthread_create(&p, NULL, serve_client, clientfd);
	}
	clean(queue);
	free(queue);
	return 0;
}