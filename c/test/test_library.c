#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "library.h"


static void test_kth_int(void **state) {
    assert_int_equal(kth((int[]){5}, 1, 1), 5);
    assert_int_equal(kth((int[]){4, 2}, 2, 1), 2);
    assert_int_equal(kth((int[]){10, 2, 1, 19, 5, 4}, 6, 3), 4);
}

int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_kth_int),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
