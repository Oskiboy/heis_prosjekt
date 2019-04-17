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
 * This struct is used in the queue .
 */
typedef struct request {
    int floor;
    elev_button_type_t direction;
    int stamp;
} request_t;

/**
 * @brief Node struct.
 * This struct is used to make the queue data structure.
 */
typedef struct node {
    request_t request;
    struct node * next;
    struct node * last;
} node_t;



struct order_queue_struct;
typedef struct order_queue_struct order_queue_t;

struct order_queue_struct{
    node_t * head;
    void (*update) (order_queue_t * self);
    void (*clear_queue) (order_queue_t * self);
    int  (*check_for_order) (order_queue_t * self, elev_motor_direction_t dir);
    elev_motor_direction_t (*get_next_direction) (order_queue_t * self, int last_floor, elev_motor_direction_t dir);
    void (*complete_order) (order_queue_t * self);
};


/**
 * @brief Prints the entire queue.
 * @param head Pointer reference to first element in queue.
 */
void print_list(node_t * head);

/**
 * @brief Push one request struct to end of queue.
 * @param head Pointer reference to first element in queue.
 * @param val Struct to be pushed.
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
 * @param self
 * @param dir
 * @return
 */
int check_for_order(order_queue_t * self, elev_motor_direction_t dir);

elev_motor_direction_t get_next_direction(order_queue_t * self, int last_floor, elev_motor_direction_t last_dir);

void clear_queue(order_queue_t * self);

void complete_order(order_queue_t * self);

void update(order_queue_t * self);



#endif //HEIS_PROSJEKT_LINKEDLIST_H
