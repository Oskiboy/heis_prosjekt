#include "fsm.h"
#include "elev.h"
#include "unity.h"
#include <unistd.h>
#include <time.h>

FSM_MODULE(fsm_test_m);
order_queue_t q;

static unsigned char obs_cmd[4]         = {10, 4, 0 , 2};
static unsigned char pos_cmd[4]         = {253, 0, 0, 70};
static unsigned char stop_btn_cmd[4]    = {10, 3, 0, 2};
static unsigned char reset_cmd[4]       = {254, 0, 0, 0};

int return_zero() {
    return 0;
}

int return_one() {
    return 1;
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
int no_order(order_queue_t* dumme, elev_motor_direction_t dir) {
    return 0;
}
void setUp(void) {
    //Should set dummy functions in the q mock class,
    //reset the elevator position and if possible reset the buttons.
    q.complete_order=empty_function;
    q.clear_queue=empty_function;
    q.next_order=motor_dir;
    q.check_for_order=order;
    fsm_test_m._dir = 0;
    write_to_socket(reset_cmd);
}

void tearDown(void) {

}

void test_init_state_stop_button(void) {
    write_to_socket(stop_btn_cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[INIT_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(STOP_STATE, fsm_test_m.state, "Init state does not stop when stop button is pressed!");
    sleep(1);
}

void test_up_state_stop_button(void) {
    write_to_socket(stop_btn_cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[UP_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(STOP_STATE, fsm_test_m.state, "Up state does not stop when stop button is pressed!");
    sleep(1);
}

void test_down_state_stop_button(void) {
    write_to_socket(stop_btn_cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[DOWN_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(STOP_STATE, fsm_test_m.state, "Down state does not stop when stop button is pressed!");
    sleep(1);
}

void test_standby_state_stop_button(void) {
    write_to_socket(stop_btn_cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[STANDBY_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(STOP_STATE, fsm_test_m.state, "Standby state does not stop when stop button is pressed!");
    sleep(1);

}
void test_serve_state_stop_button(void) {
    write_to_socket(stop_btn_cmd);
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[SERVE_ORDER_STATE];
    fsm_test_m.state = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(STOP_STATE, fsm_test_m.state, "Serve order state does not stop when stop button is pressed!");
}

void test_init_obstruction_handling(void) {
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[INIT_STATE];
    write_to_socket(obs_cmd);   //Set the obstruction button
    int ret = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(INIT_STATE, ret, "Obstruction button is pressed, should stay in init state");
}

void test_init_state_transitions(void) {
    write_to_socket(pos_cmd);   //Resets the elevator to a little below second floor
    int ret = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(INIT_STATE, ret, "As the elevator is not at a floor, the init state should not transition.");
    time_t stamp = time(NULL);
    while(time(NULL) - stamp <= 3) {
        ret = fsm_test_m.current_state_function(&fsm_test_m, &q);
    }
    TEST_ASSERT_EQUAL_MESSAGE(STANDBY_STATE, ret, "As the elevator should have reached the bottom floor, the fsm should transition");
}

void test_door_should_open_for_3_seconds_when_serving_order(void) {
    //We want to run the serve order state to check if the door actually stays open for three ish seconds.
    int ret = 0;
    fsm_test_m.current_state_function = fsm_test_m.state_function_array[SERVE_ORDER_STATE];
    q.check_for_order = order;
    fsm_test_m.current_state_function(&fsm_test_m, &q);
    q.check_for_order = no_order;
    ret = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(SERVE_ORDER_STATE, ret, "Doors closed too quickly in serve order state");
    sleep(1);
    ret = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(SERVE_ORDER_STATE, ret, "Only one second has passed!");
    sleep(1);
    ret = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(SERVE_ORDER_STATE, ret, "Only two seconds has passed!");
    sleep(1);
    ret = fsm_test_m.current_state_function(&fsm_test_m, &q);
    TEST_ASSERT_EQUAL_MESSAGE(STANDBY_STATE, ret, "Three seconds should have passed! Elevator should transition");

}

void state_array_index_test(void) {
    TEST_ASSERT_EQUAL_MESSAGE(init_state_function, fsm_test_m.state_function_array[INIT_STATE], "INIT state at wrong index");
    TEST_ASSERT_EQUAL_MESSAGE(standby_state_function, fsm_test_m.state_function_array[STANDBY_STATE], "STANDBY state at wrong index");
    TEST_ASSERT_EQUAL_MESSAGE(up_state_function, fsm_test_m.state_function_array[UP_STATE], "UP state at wrong index");
    TEST_ASSERT_EQUAL_MESSAGE(down_state_function, fsm_test_m.state_function_array[DOWN_STATE], "DOWN state at wrong index");
    TEST_ASSERT_EQUAL_MESSAGE(stop_state_function, fsm_test_m.state_function_array[STOP_STATE], "STOP state at wrong index");
    TEST_ASSERT_EQUAL_MESSAGE(serve_order_state_function, fsm_test_m.state_function_array[SERVE_ORDER_STATE], "SERVE_ORDER state at wrong index");
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(state_array_index_test);
    RUN_TEST(test_init_obstruction_handling);
    RUN_TEST(test_init_state_transitions);
    RUN_TEST(test_door_should_open_for_3_seconds_when_serving_order);
    RUN_TEST(test_init_state_stop_button);
    RUN_TEST(test_up_state_stop_button);
    RUN_TEST(test_down_state_stop_button);
    RUN_TEST(test_standby_state_stop_button);
    RUN_TEST(test_serve_state_stop_button);
    return UNITY_END();
}