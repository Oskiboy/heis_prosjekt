#include "fsm.h"
#include "elev.h"

int run_fsm(fsm_t* fsm_p) {
    while(1) {
        fsm_p->state = fsm_p->current_state_function(fsm_p);
        fsm_p->current_state_function = fsm_p->state_function_array[fsm_p->state];
    }
}

state_t up_state_function(fsm_t* fsm_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }
    return UP_STATE;
}

state_t down_state_function(fsm_t* fsm_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }
    if(fsm_p->dir != DIRN_DOWN) {
        elev_set_motor_direction(DIRN_DOWN);
        fsm_p->dir = DIRN_DOWN;
    }
    
    return DOWN_STATE;
}

state_t standby_state_function(fsm_t* fsm_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }

    return STANDBY_STATE;
}

state_t stop_state_function(fsm_t* fsm_p) {
    if(fsm_p->dir != DIRN_STOP) {
        elev_set_motor_direction(DIRN_STOP);
        fsm_p->dir = DIRN_STOP;
    }

    if(elev_get_floor_sensor_signal() > 0) {
        elev_set_door_open_lamp(1);
    }

    if(!elev_get_stop_signal()) {
        if(fsm_p->init)
            return STANDBY_STATE;
        else
            return INIT_STATE; 
    }

    return STOP_STATE;
}

state_t init_state_function(fsm_t* fsm_p) {
    if(elev_get_stop_signal()) {
        return STOP_STATE;
    }

    if(elev_get_obstruction_signal()) {
        return INIT_STATE;
    }

    if(fsm_p->dir == DIRN_DOWN) {
        elev_set_motor_direction(DIRN_DOWN);
    }

    if(elev_get_floor_sensor_signal > 0) {
        fsm_p->init = 1;
        return STANDBY_STATE;
    }
    return INIT_STATE;
}