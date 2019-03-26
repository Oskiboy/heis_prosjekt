#include "fsm.h"
#include "unity.h"

FSM_MODULE(fsm_test_m);

void setUp(void) {

}

void tearDown(void) {

}

void stop_test(void) {
    
}


int main(int argc, char** argv) {
    UNITY_BEGIN();

    RUN_TEST(stop_test);

    return UNITY_END();
}