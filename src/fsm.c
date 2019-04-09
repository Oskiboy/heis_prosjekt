#include "fsm.h"
#include "elev.h"
#include "stdio.h"

int run_fsm(fsm_t* fsm_p, order_queue_t* queue_p) {
    //If the FSM has no queue, return an error.
    if(!queue_p)
        return -1;
    while(1) {
        if(fsm_p->state != STOP_STATE) {
            queue_p->update(queue_p);
        }
        fsm_p->state = fsm_p->current_state_function(fsm_p, queue_p);
        fsm_p->current_state_function = fsm_p->state_function_array[fsm_p->state];
    }
}

state_t up_state_function(fsm_t* fsm_p, order_queue_t* queue_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }

    //Start the motor.
    if(elev_get_floor_sensor_signal() == 3) {
        elev_set_motor_direction(DIRN_STOP);
        fsm_p->_dir = DIRN_STOP;
    } else if(fsm_p->_dir != DIRN_UP) {
        elev_set_motor_direction(DIRN_UP);
        fsm_p->_dir = DIRN_UP;
    }

    //If we have an order on the current floor with the correct direction, stop.
    if(queue_p->check_for_order(queue_p, fsm_p->_dir) > 0){
        return SERVE_ORDER_STATE;
    }

    return UP_STATE;
}

state_t down_state_function(fsm_t* fsm_p, order_queue_t* queue_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }

    //Start the motor.
    if(elev_get_floor_sensor_signal() == 0) {
        elev_set_motor_direction(DIRN_STOP);
        fsm_p->_dir = DIRN_STOP;
    } else if(fsm_p->_dir != DIRN_DOWN) {
        elev_set_motor_direction(DIRN_DOWN);
        fsm_p->_dir = DIRN_DOWN;
    }

    //If we have an order on the current floor with the correct direction, stop.
    if(queue_p->check_for_order(queue_p, fsm_p->_dir) > 0){
        return SERVE_ORDER_STATE;
    }
    
    return DOWN_STATE;
}

state_t standby_state_function(fsm_t* fsm_p, order_queue_t* queue_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }

    //Check if we have an active order and transition to the appropriate state.
    switch (queue_p->next_order(queue_p))
    {
        case DIRN_UP:
            return UP_STATE;
            break;
        case DIRN_DOWN:
            return DOWN_STATE;
            break;
        case DIRN_STOP:
            return STANDBY_STATE;
            break;
        default:
            break;
    }

    return STANDBY_STATE;
}

state_t serve_order_state_function(fsm_t* fsm_p, order_queue_t* queue_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }

    if(queue_p->check_for_order(queue_p, fsm_p->_dir)) {
        queue_p->complete_order();
        elev_set_motor_direction(DIRN_STOP);
        fsm_p->_timestamp = time(NULL);
        elev_set_door_open_lamp(1);
    } else if(time(NULL) - fsm_p->_timestamp >= 3) {
        elev_set_door_open_lamp(0);
        //Order completed!
        return STANDBY_STATE;
    }

    return SERVE_ORDER_STATE;
}

state_t stop_state_function(fsm_t* fsm_p, order_queue_t* queue_p) {
    //If the motor is running, stop it.
    if(fsm_p->_dir != DIRN_STOP) {
        elev_set_motor_direction(DIRN_STOP);
        fsm_p->_dir = DIRN_STOP;
    }
    
    //Clear the queue if it is not empty
    if(queue_p->check_for_order(queue_p, fsm_p->_dir) < 0) {
        queue_p->clear_queue(queue_p);
    }

    //If the elevator is at a floor, it should open the doors.
    if(elev_get_floor_sensor_signal() >= 0) {
        elev_set_door_open_lamp(1);
    }

    //When the stop button is released, return to either standby or init.
    if(!elev_get_stop_signal()) {
        if(fsm_p->_init)
            return STANDBY_STATE;
        else
            return INIT_STATE; 
    }

    return STOP_STATE;
}

state_t init_state_function(fsm_t* fsm_p, order_queue_t* queue_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }

    if(elev_get_obstruction_signal()) {
        return INIT_STATE;
    }

    if(fsm_p->_dir != DIRN_DOWN) {
        elev_set_motor_direction(DIRN_DOWN);
        fsm_p->_dir = DIRN_DOWN;
    }
    int floor = elev_get_floor_sensor_signal();
    if(floor >= 0) {
        fsm_p->_init = 1;
        elev_set_motor_direction(DIRN_STOP);
        fsm_p->_dir = DIRN_STOP;
        return STANDBY_STATE;
    }
    return INIT_STATE;
}
