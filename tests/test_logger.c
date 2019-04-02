#include "logger.h"
#include "unity.h"
#include <stdio.h>


void setUp(void) {
    printf("Setting up logger\n");
    char* filename = "test.log";
    logger_init(filename);
}

void tearDown(void) {
    printf("Closing logger\n");
    logger_close();
}

void info_log_test(void) {
    log_info("THIS IS AN INFO TEST");
}

void error_log_test(void) {
    log_error("THIS IS AN ERROR TEST");
}

void fatal_log_test(void) {
    log_fatal("THIS IS A FATAL TEST");
}

int main(int argc, char** argv) {
    UNITY_BEGIN();

    RUN_TEST(info_log_test);
    RUN_TEST(error_log_test);
    RUN_TEST(fatal_log_test);

    return UNITY_END();
}