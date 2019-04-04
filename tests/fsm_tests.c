#include "fsm.h"
#include "elev.h"
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
}

void tearDown(void) {

}

void stop_test(void) {
    static char cmd[4] = {10, 3, 0, 255};
    write_to_socket(cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[INIT_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL(STOP_STATE, fsm_test_m.state);
    write_to_socket(cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[UP_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL(STOP_STATE, fsm_test_m.state);
    write_to_socket(cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[DOWN_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL(STOP_STATE, fsm_test_m.state);
    write_to_socket(cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[STANDBY_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL(STOP_STATE, fsm_test_m.state);
    write_to_socket(cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[SERVE_ORDER_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL(STOP_STATE, fsm_test_m.state);
}


int main(int argc, char** argv) {
    UNITY_BEGIN();
    elev_init();
    RUN_TEST(stop_test);
    return UNITY_END();
}