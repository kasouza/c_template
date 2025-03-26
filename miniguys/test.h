#ifndef KASOUZA_MG_TEST_H
#define KASOUZA_MG_TEST_H

/* == Configurations == */

#ifndef MAX_TESTS
#define MAX_TESTS 32
#endif

/* ==================== */

/* === Header stuff === */
#include <stdbool.h>
#include <stdio.h> // IWYU pragma: keep
#include <assert.h>

typedef bool (*t_test_func)();
typedef struct {
    const char *name;
    t_test_func test;
} t_Test;

#define t_REGISTER_TEST(test) t_register_named_test(#test, test)

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

/* ==================== */

/* == Implementation == */
#ifdef KASOUZA_TEST_IMPL
static size_t tests_len = 0;
static t_Test tests[MAX_TESTS];

void t_register_named_test(const char *name, t_test_func test) {
    assert(tests_len <= MAX_TESTS && "Max number of tests reached");
    tests[tests_len++] = (t_Test){.name = name, .test = test};
}

void t_run_tests() {
    printf("Total tests: %ld\n\n", tests_len);
    int failed = 0;
    for (size_t i = 0; i < tests_len; i++) {
        bool result = tests[i].test();

        if (!result) {
            printf("\x1B[31m    - IN TEST:\x1B[0m %s\n", tests[i].name);
            failed++;
        }

        printf("\x1B[32mSUCCESS: %s\x1B[0m\n", tests[i].name);
    }

    int sucessfull = tests_len - failed;
    printf("\nFINISHED \x1B[32m%d sucessfull \x1B[0mand \x1B[31m%d "
           "failed\x1B[0m\n",
           sucessfull, failed);
}
#endif
/* ==================== */

#endif
