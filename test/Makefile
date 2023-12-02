CC = clang
SRCS = bst_test.c list_test.c
HEADERS = unity/unity.c $(HDIR)/src/type.c $(HDIR)/src/err.c $(HDIR)/src/list.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
.c.o:
	$(CC) -g -I $(HDIR) $(HEADERS) $< -o $@
 
check:
	for obj in $(OBJS); do $(HDIR)/test/$$obj; done;