#ifndef KASOUZA_JOGUINHO_TEST_TEST_TEST_H
#define KASOUZA_JOGUINHO_TEST_TEST_TEST_H

#include <stdbool.h>
#include <stdio.h>

#define MAX_TESTS 32

typedef bool (*t_test_func)();
typedef struct {
    const char *name;
    t_test_func test;
} t_Test;

#define t_register_test(test) t_register_named_test(#test, test)

#define t_ASSERT(condition)                                                    \
    do {                                                                       \
        if (!(condition)) {                                                    \
            printf("\x1B[31mFAILED\x1B[0m [%s, %d] - %s\n", __FILE__,          \
                   __LINE__, #condition);                                      \
            return false;                                                      \
        }                                                                      \
    } while (0)

void t_register_named_test(const char *name, t_test_func test);
void t_run_tests();

#endif
