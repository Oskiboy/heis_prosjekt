#include "fsm.h"
#include "unity.h"

FSM_MODULE(fsm_test_m);
order_queue_t q;

int return_zero() {
    return 0;
}
void empty_function() {
    return;
}
elev_motor_direction_t motor_dir(order_queue_t* dummy) {
    return 1;
}
int order(order_queue_t* dummy, elev_motor_direction_t dir) {
    return 1;
}
void setUp(void) {
    q.complete_order=empty_function;
    q.clear_queue=empty_function;
    q.next_order=motor_dir;
    q.check_for_order=order;
    elev_init();
}

void tearDown(void) {

}

void stop_test(void) {
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[INIT_STATE];
    fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL(fsm_test_m.state, STOP_STATE);
}


int main(int argc, char** argv) {
    UNITY_BEGIN();

    RUN_TEST(stop_test);

    return UNITY_END();
}