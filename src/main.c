#include "socket_wrapped.h"
#include "type.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int setup_listenfd(uint16_t port);

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

static char *data = NULL;
void serve_producer(int clientfd) {
	struct bst str;
	read_bst(clientfd, &str);
	free(data);
	data = str.str;
}

void serve_consumer(int clientfd) {
	struct bst tmp;
	if (data != NULL) {
		tmp.length = strlen(data);
		tmp.str = data;
		write_bst(clientfd, &tmp);
		free(data);
		data = NULL;
	} else {
		tmp.length = strlen("NULL");
		tmp.str = "NULL";
		write_bst(clientfd, &tmp);
	}
}

void serve_client(int clientfd) {
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
}

int main(int argc, char **argv) {
	int listenfd = setup_listenfd(8000), clientfd;

	while (true) {
		clientfd = _accept(listenfd, (struct sockaddr *)NULL, 0);
		serve_client(clientfd);
	}
	free(data);
	return 0;
}