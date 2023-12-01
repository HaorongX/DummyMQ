CC = clang
SRCS = main.c producer.c consumer.c
HEADERS = type.c err.c socket_wrapped.c list.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
.c.o:
	$(CC) -g $(HEADERS) $< -o $@