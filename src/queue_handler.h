//
// Created by emil on 26.03.19.
//

#ifndef HEIS_PROSJEKT_LINKEDLIST_H
#define HEIS_PROSJEKT_LINKEDLIST_H

#include <stdlib.h>
#include <time.h>
#include "elev.h"


/**
 * @file
 * @brief The Queue interface.
 * To create a Queue module to use add the QUEUE_MODULE macro with your defines and includes.
 */

/**
 * @def QUEUE_MODULE(_name)
 * This macro is used to create and instantiate a new order_queue_struct.
 * This should always have a unique name and the run queue function should be passed a pointer to this module.
 * @param _name This is the name given to the new module.
 */
#define QUEUE_MODULE(_name)    \
static order_queue_t _name = {  \
NULL, update,    \
clear_queue, check_for_order,   \
get_next_direction, complete_order  \
}

//Now pass the module to the run_fsm(fsm_t* fsm_p) function

/**
 * @brief Request struct.
 * This struct is used in the queue to contain the data for each request.
 */
typedef struct request {
    int floor; ///< The floor of the request
    elev_button_type_t direction; ///< Type of request BUTTON_CALL_UP, BUTTON_CALL_DOWN, BUTTON_COMMAND
    int stamp; ///< Stamp on each request, not used at the moment but could be used in the future to add an efficient sorting algorithm to the queue
} request_t;

/**
 * @brief Node struct.
 * This struct is used to make the queue data structure.
 */
typedef struct node {
    request_t request;  ///< The nodes data.
    struct node * next; ///< Pointer to next node
    struct node * last; ///< Pointer to the last node.
} node_t;

struct order_queue_struct;

/**
 * @brief Typedefs the order_queue_struct to a readable representation.
 * 
 */
typedef struct order_queue_struct order_queue_t;


/**
 * @struct order_queue_struct
 * @brief The struct that implements the queue module
 */
struct order_queue_struct{
    node_t * head; ///< Pointer to the first element in the queue
    void (*update) (order_queue_t * self); ///< Function that will update the state of the queue
    void (*clear_queue) (order_queue_t * self); ///< Clears the queue
    int  (*check_for_order) (order_queue_t * self, elev_motor_direction_t dir); ///< Checks for an existing order
    elev_motor_direction_t (*get_next_direction) (order_queue_t * self, int last_floor, elev_motor_direction_t dir); ///< Returns the next direction to travel.
    void (*complete_order) (order_queue_t * self); ///< Completes the order of the current floor, removing it from the queue.
};


/**
 * @brief Prints the entire queue.
 * @param head Pointer reference to first element in queue.
 */
void print_list(node_t * head);

/**
 * @brief Push one request struct to end of queue.
 * @param head Pointer reference to first element in queue.
 * @param val request_t struct to be pushed to the queue.
 */
void push(node_t ** head, request_t val);

/**
 * @brief Pop the first request in queue.
 * @param head Pointer reference to first element in queue.
 */
void pop(node_t ** head);

/**
 * @brief Remove the last request in queue.
 * @param head Pointer reference to first element in queue.
 */
void remove_last(node_t ** head);

/**
 * @brief Remove the request in queue pointed to by the node parameter.
 * @param head Pointer reference to first element in queue.
 * @param node Pointer reference to request to be removed.
 */
node_t * remove_node(node_t ** head, node_t ** node);

/**
 * @brief Delete all requests in queue leaving it empty.
 * @param head Pointer reference to first element in queue.
 */
void delete_list(node_t ** head);

/**
 * @brief Tells whether the elevator should stop at the current floor
 * @param head Pointer reference to first element in queue.
 * @param dir The current direction
 * @param floor The current floor
 * @return -1: empty queue, 0: no stop request at current floor, 1: stop request at current floor.
 */
int get_order(node_t ** head, elev_button_type_t dir, int floor);


/**
 * @brief Clears orders compleated if the elevator stop at the current floor.
 * @param head Pointer reference to first element in queue.
 * @param floor The current floor
 */
void clear_order(node_t ** head, int floor);


/**
 *
 * @param self Pointer to a order_queue_t object
 * @param dir Direction of the elevator
 * @return -1: empty queue, 0: no stop request at current floor, 1: stop request at current floor.
 */
int check_for_order(order_queue_t * self, elev_motor_direction_t dir);

/**
 *
 * @param self Pointer to a order_queue_t object
 * @param last_floor Last floor visited
 * @param last_dir Last direction of the elevator
 * @return The direction the elevator should take
 */
elev_motor_direction_t get_next_direction(order_queue_t * self, int last_floor, elev_motor_direction_t last_dir);

/**
 * @brief Delete all requests in queue
 * @param self Pointer to a order_queue_t object
 */
void clear_queue(order_queue_t * self);

/**
 * @brief Deletes all requests in queue on the current floor
 * @param self Pointer to a order_queue_t object
 */
void complete_order(order_queue_t * self);

/**
 * @brief Fetches button commands and pushes requests to the queue
 * @param self Pointer to a order_queue_t object
 */
void update(order_queue_t * self);



#endif //HEIS_PROSJEKT_LINKEDLIST_H
