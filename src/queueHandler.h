//
// Created by emil on 26.03.19.
//

#ifndef HEIS_PROSJEKT_LINKEDLIST_H
#define HEIS_PROSJEKT_LINKEDLIST_H
#include <stdlib.h>
#include "elev.h"
#endif //HEIS_PROSJEKT_LINKEDLIST_H



typedef struct request {
    int floor;
    elev_motor_direction_t direction;
    int stamp;
} request_t;

typedef struct node {
    request_t request;
    struct node * next;
    struct node * last;
} node_t;

/*typedef struct {
    int (*check_for_order)(queue_handler_t* self, elev_motor_direction_t dir, int floor);
    node_t* _head;
}queue_handler_t;*/

node_t* init_list(request_t request);

void print_list(node_t * head);

void push(node_t ** head, request_t val);

void pop(node_t ** head);

void remove_last(node_t ** head);

node_t * remove_node(node_t ** head, node_t ** node);

void remove_by_index(node_t ** head, int n);

void delete_list(node_t ** head);

int check_for_order(node_t ** head, elev_motor_direction_t dir, int floor);

void update(node_t * head);

void clear_queue(node_t * head);

