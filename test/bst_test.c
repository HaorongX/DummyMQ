#include "test/unity/unity_internals.h"
#include "unity/unity.h"
#include "src/type.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int fd[2];
void setUp(void)
{
    pipe(fd);
}

void tearDown(void)
{
    close(fd[0]);
    close(fd[1]);
}

void test_read_bst(void)
{
    char *d = "helloworld";
    size_t k = strlen(d);
    struct bst s;
    write(fd[1], &k, sizeof(k));
    write(fd[1], d, sizeof(char) * strlen(d));
    read_bst(fd[0], &s);
    if(strcmp(d, s.str) || (s.length != k))
        TEST_FAIL();
}

void test_write_bst(void)
{
    struct bst s = {3, "ddd"}, d;
    write_bst(fd[1], &s);
    read(fd[0], &d.length, sizeof(d.length));
    d.str = (char*)calloc(d.length, sizeof(char));
    read(fd[0], d.str, d.length);
    if(strcmp(d.str, s.str) || (s.length != d.length))
        TEST_FAIL();
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_read_bst);
    RUN_TEST(test_write_bst);
    return UNITY_END();
}