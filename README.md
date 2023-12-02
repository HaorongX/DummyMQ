![LOGO](logo-color.png)

**DummyMQ** is a simple, lightweight message queue server written in C.

**This project is still under heavy development, so it only contains some basic functions currently.**

### Features
- Lightweight: Just some C code, less than 7 kb.

- Speed: Send/receive 10000+ messages per second on an average machine. 

- Easy to setup: All you need to do its run `git fetch` & `make`

### Usage


The messages will be stored in a FIFO (first in first out) queue.

After setting up **DummyMQ**  server, all you need to do is to connect to it in your own client(via TCP protocol).

Every single package sent to the server will be a bst structure(please refer to src/type.h).

A bst structure is just a string with its length, the definition is as follow:

```C
struct bst {
	size_t length; // length of the string
	char *str;	   // data
};
```

After building connection, you need to declare your identity(producer or consumer), by sending "PRO" for producer or "CON" for consumer within a bst.(src/producer.c & src/consumer.c provide sample consumer & producer, please check them out)

**If your client runs as a producer**
Then all your package sent to the server wiil be added to the default queue. Server will NOT return anything.

**If your client runs as a consumer**
Then after declaring your identity, the server will return a bst and close the connection at once.

This bst is either the data at the tail of the queue, or just a string "NULL"(when the queue is empty yet).

### Installation

```sh
git git@github.com:HaorongX/DummyMQ.git
cd ./DummyMq
make
```
No external modules required, except for GNU-make.

### Get involved

**Everyone is welcomed to make contribution!**

If you want any features / find any bugs please [create an issue here](https://github.com/HaorongX/DummyMQ/issues/new). When reporting a bug, please try describing how to reproduce it.

If you have any ideas and want to hack into this project, please [open a pull request](https://github.com/HaorongX/DummyMQ/pulls).