#include "test_lib.h"
#include "unity.h"
#include <stdio.h>

void setUp(void) {
    printf("This is a setup!\n");
}

void tearDown(void) {
    printf("This is tear down!\n");
}

void test_dummy_1(void) {
    TEST_ASSERT(1);
    dummy_1();
}

void test_dummy_2(void) {
    TEST_ASSERT(dummy_2());
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(test_dummy_1);
    RUN_TEST(test_dummy_2);

    return UNITY_END();
}