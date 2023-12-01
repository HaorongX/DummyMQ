#include "src/list.h"
#include "test/unity/unity_internals.h"
#include "unity/unity.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct blist *l;
void setUp(void) { l = create_list(); }

void test_append() {
	char data[][6] = {"data1", "data2", "data3"};
	int i;
	for (i = 0; i < 3; ++i) {
		struct lnode *n = append(l, (void *)data[i]);
		if (strcmp((char *)n->data, data[i]))
			TEST_FAIL();
	}
}

void test_pop() {
	char data[][6] = {"data1", "data2", "data3"};
	int i;
	for (i = 0; i < 3; ++i)
		append(l, (void *)data[i]);
	for (i = 0; i < 3; ++i) {
		struct lnode *n = pop(l);
		if (strcmp((char *)n->data, data[i]))
			TEST_FAIL();
	}
	if (!empty(l))
		TEST_FAIL();
}

void test_clean() {
	clean(l);
	clean(l);

	append(l, (void *)"data");
	clean(l);

	append(l, (void *)"data");
	append(l, (void *)"data");
	append(l, (void *)"data");
	clean(l);
}

void tearDown(void) { free(l); }

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_append);
	RUN_TEST(test_pop);
	RUN_TEST(test_clean);
	return UNITY_END();
}