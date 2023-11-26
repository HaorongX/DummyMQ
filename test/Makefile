CC = clang
SRCS = bst_test.c
HEADERS = unity/unity.c $(HDIR)/src/type.c $(HDIR)/src/err.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
.c.o:
	$(CC) -I $(HDIR) $(HEADERS) $< -o $@