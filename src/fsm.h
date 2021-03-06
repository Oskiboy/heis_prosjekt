#ifndef FSM_H
#define FSM_H

#include "elev.h"
#include "queue_handler.h"

#include "time.h"

/**
 * @file 
 * @brief The FSM interface.
 * To create an FSM module to use add the FSM_MODULE macro with your defines and includes.
 * To run the state machine, pass the module pointer to the run_fsm(fsm_t* fsm_p) function and the FSM will start its
 * infinite loop.
 */ 

/**
 * @def FSM_MODULE(_name)
 * This macro is used to create and instantiate a new fsm_module_struct.
 * This should always have a unique name and the run_fsm function should be passed a pointer to this module.
 * This method of initialization is to make sure the module is always properly initialized for the user and 
 * a way for the maintainer to have a flexible interface to the user.
 * @param _name This is the name given to the new module. 
 */
#define FSM_MODULE(_name)   \
static fsm_t _name =        \
{INIT_STATE,                \
0,                          \
DIRN_STOP,                  \
init_state_function,        \
{                           \
up_state_function,          \
down_state_function,        \
standby_state_function,     \
serve_order_state_function, \
stop_state_function,        \
init_state_function         \
},                          \
-1,                         \
DIRN_STOP                   \
};

enum state_enumeration;
struct fsm_module_struct;

/**
 * @brief The state_t connects states to their indexes in the state array.
 * 
 */
typedef enum state_enumeration state_t;

/**
 * @brief The fsm_t holds an instance of the state machine module.
 * 
 */
typedef struct fsm_module_struct fsm_t;

/**
 * @brief Defines the prototype of all state functions
 * To have an easy expandable interface, all state functions follow this 
 * prototype, so that they can be fitted into the state function array.
 */
typedef state_t (*state_function_t)(fsm_t* fsm_p, order_queue_t* queue_p);

/**
 * @brief All states have a corresponding state constant.
 * To make the states as explicit as possible using a enum and then typedefing 
 * that enum will make the code overall easier to read. It also gives warnings if you try to 
 * implicitly convert for example an int to a state_t
 * 
 */
enum state_enumeration {
    UP_STATE,
    DOWN_STATE,
    STANDBY_STATE,
    SERVE_ORDER_STATE,
    STOP_STATE,
    INIT_STATE,
    STATES_N
};


/**
 * @struct fsm_module_struct
 * @brief The fsm struct that implements the fsm module
 */
struct fsm_module_struct{
    state_t                     state;  ///< Holds the current state
    int                         _init;  ///< When the elevator has gotten to a well defined state, this will be set to 1.
    elev_motor_direction_t      _dir;   ///< Keeps track of the current direction.
    state_function_t            current_state_function;         ///< The current state function is run every loop.
    const state_function_t      state_function_array[STATES_N]; ///< A constant array that holds all the different state functions.
    time_t                      _timestamp;     ///<  A way to keep track of the time passed when timing door opening and closing.
    int                         _last_floor;    ///< To remember our position in case of stopping.
    elev_motor_direction_t      _last_dir;      ///< Also to remember which way we moved after stopping.
};

/**
 * @brief Run the state machine.
 * @remark This function is blocking
 * 
 * This takes in a pointer to the FSM module generated by FSM_MODULE and runs the state machine.
 * 
 * @param fsm_p Pointer to the FSM object 
 * @param queue_p  Pointer to the order queue handler.
 * @return int Error message
 */
int run_fsm(fsm_t* fsm_p, order_queue_t* queue_p);

/**
 * @brief While the elevator is going up, this state is run.
 * 
 * @param fsm_p Pointer to a FSM object.
 * @param queue_p  Pointer to an order queue handler.
 * @return state_t The next state that the FSM should transition to.
 */
state_t up_state_function(fsm_t* fsm_p, order_queue_t* queue_p);

/**
 * @brief While the elevator is going down, this state is run.
 * 
 * @param fsm_p Pointer to a FSM object.
 * @param queue_p  Pointer to an order queue handler.
 * @return state_t The next state that the FSM should transition to.
 */
state_t down_state_function(fsm_t* fsm_p, order_queue_t* queue_p);

/**
 * @brief While the elevator is at a standstill, this state is run.
 * 
 * @param fsm_p Pointer to a FSM object.
 * @param queue_p  Pointer to an order queue handler.
 * @return state_t The next state that the FSM should transisiton to.
 */
state_t standby_state_function(fsm_t* fsm_p, order_queue_t* queue_p);

/**
 * @brief When the FSM is at a floor with an order, this state serves it.
 * 
 * @param fsm_p Pointer to an fsm object
 * @param queue_p  Pointer to an order queue handler.
 * @return state_t The next state
 */
state_t serve_order_state_function(fsm_t* fsm_p, order_queue_t* queue_p);

/**
 * @brief When the stop button is pressed, this state will be run.
 * 
 * @param fsm_p Pointer to a FSM object.
 * @param queue_p  Pointer to an order queue handler.
 * @return state_t The next state that the FSM should transition to.
 */
state_t stop_state_function(fsm_t* fsm_p, order_queue_t* queue_p);

/**
 * @brief While the elevator is initializing, this state will be run.
 * 
 * @param fsm_p Pointer to a FSM object.
 * @param queue_p  Pointer to an order queue handler.
 * @return state_t The next state that the FSM should transition to.
 */
state_t init_state_function(fsm_t* fsm_p, order_queue_t* queue_p);


#endif //FSM_H
