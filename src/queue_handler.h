//
// Created by emil on 26.03.19.
//

#ifndef HEIS_PROSJEKT_LINKEDLIST_H
#define HEIS_PROSJEKT_LINKEDLIST_H

#include <stdlib.h>
#include <time.h>
#include "elev.h"

#define QUEUE_MODULE(_name)    \
static order_queue_t _name = {  \
NULL, update,    \
clear_queue, check_for_order,   \
next_order, complete_order  \
}


typedef struct request {
    int floor;
    elev_button_type_t direction;
    int stamp;
} request_t;

typedef struct node {
    request_t request;
    struct node * next;
    struct node * last;
} node_t;

struct order_queue_struct;
typedef struct order_queue_struct order_queue_t;

struct order_queue_struct{
    node_t * head;
    long int start_time = time(NULL);
    void (*update) (order_queue_t * self);
    void (*clear_queue) (order_queue_t * self);
    int  (*check_for_order) (order_queue_t * self, elev_motor_direction_t dir);
    elev_motor_direction_t (*next_order) (order_queue_t * self);
    void (*complete_order) (order_queue_t * self);
};


node_t* init_list(request_t request);

void print_list(node_t * head);

void push(node_t ** head, request_t val);

void pop(node_t ** head);

void remove_last(node_t ** head);

node_t * remove_node(node_t ** head, node_t ** node);

void remove_by_index(node_t ** head, int n);

void delete_list(node_t ** head);

int get_order(node_t ** head, elev_button_type_t dir, int floor);

void clear_order(node_t ** head, int floor);

int check_for_order(order_queue_t * self, elev_motor_direction_t dir);

elev_motor_direction_t next_order(order_queue_t * self);

void clear_queue(order_queue_t * self);

void complete_order(order_queue_t * self);

void update(order_queue_t * self);



#endif //HEIS_PROSJEKT_LINKEDLIST_H
