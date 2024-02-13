#include "saske.h"
#include "test.h"

bool test_fodase() {
    t_ASSERT(true == false);
    return true;
}
bool test_saske() {
    t_ASSERT(true == true);
    return true;
}

int main(void) {
    t_register_test(test_saske);
    t_register_test(test_fodase);
    t_run_tests();
    return 0;
}
