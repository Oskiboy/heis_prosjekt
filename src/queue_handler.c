//
// Created by emil on 26.03.19.
//

#include "queue_handler.h"
#include <stdio.h>


void print_list(node_t * head) {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    node_t * current = head;
    int i = 0;
    while (current != NULL) {
        printf("Request:%-3d     Floor:%-2d  Type: ",i,current->request.floor);
        switch (current->request.direction) {
            case BUTTON_CALL_UP: printf("Up  ");
                break;
            case BUTTON_CALL_DOWN: printf("Down");
                break;
            case BUTTON_COMMAND: printf("Stop");
                break;
        }
        printf("   Stamp: %d\n", current->request.stamp);
        current = current->next;
        i++;
    }
}

void push(node_t ** head, request_t request) {
    if(*head == NULL) {
        (*head) = malloc(sizeof(node_t));
        (*head)->request = request;
        (*head)->next = NULL;
        (*head)->last = NULL;
        return;
    }
    node_t * current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->request = request;
    current->next->next = NULL;
    current->next->last = current;
}

void pop(node_t ** head) {
    if (*head == NULL) {
        return;
    }

    node_t * next_node;
    next_node = (*head)->next;
    free(*head);
    *head = next_node;

}

void remove_last(node_t ** head) {
    node_t * temp_p;
    if (*head == NULL) {
        return;
    }

    /* if there is only one item in the list, remove it */
    if ((*head)->next == NULL) {
        pop(head);
        return;
    }

    /* get to the second to last node in the list */
    node_t * current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    temp_p = current->next;
    free(temp_p);
    current->next = NULL;

}

node_t * remove_node(node_t ** head, node_t ** node){
    node_t * temp_p;
    node_t * out_p;
    if (((*node)->last == NULL) && !((*node)->next == NULL)){
        temp_p = (*node);
        *head = (*node)->next;
        (*head)->last = NULL;
        free(temp_p);
        return *head;

    }
    else if(((*node)->last == NULL) && ((*node)->next == NULL)){
        temp_p = (*node);
        *head = NULL;
        *node = NULL;
        free(temp_p);
        return NULL;
    }
    else if ((*node)->next == NULL){
        temp_p = (*node)->last;
        temp_p->next = NULL;
        temp_p = (*node);
        free(temp_p);
        return NULL;
    }


    temp_p = (*node)->next;
    temp_p->last = (*node)->last;
    temp_p = (*node)->last;
    temp_p->next = (*node)->next;
    temp_p = (*node);
    out_p = (*node)->next;
    free(temp_p);
    return out_p;
}

void delete_list(node_t ** head){
    while(*head != NULL) pop(head);
}

int get_order(node_t ** head, elev_button_type_t dir, int floor){
    node_t * current = *head;
    if (*head == NULL) {
        return -1;
    }
    if((*head)->request.floor == floor){
        return 1;
    }
    while (current != NULL) {
        if (current->request.floor == floor &&
            (current->request.direction == dir || dir == BUTTON_COMMAND || current->request.direction == BUTTON_COMMAND)) {
            current = remove_node(head, &current);
            return 1;
        } else current = current->next;
    }
    return 0;
}

void clear_order(node_t ** head,  int floor){
    if (*head == NULL) return;
    node_t * current = *head;
    current = *head;
    while (current->next != NULL) {
        if (current->request.floor == floor) {
            current = remove_node(head, &current);
        } else current = current->next;

    }
    if (current->request.floor == floor) {
        remove_last(head);
    }
}




void update(order_queue_t * self){
    request_t temp;
    for(int floor = 0; floor<=3; ++floor){
        for(int button = 0; floor<=3; ++floor){
            if(elev_get_button_signal(button, floor)){
                temp.floor = floor;
                temp.direction = button;
                temp.stamp = time(NULL);
                push(&self->head, temp);
            }
        }
    }
}

void clear_queue(order_queue_t * self){
    delete_list(&self->head);
}

int check_for_order(order_queue_t * self, elev_motor_direction_t dir){
    if (dir == DIRN_DOWN){
        return get_order(&self->head, BUTTON_CALL_DOWN, elev_get_floor_sensor_signal());
    }
    else if (dir == DIRN_UP){
        return get_order(&self->head, BUTTON_CALL_UP, elev_get_floor_sensor_signal());
    }
    else if (dir == DIRN_STOP){
        return get_order(&self->head, BUTTON_COMMAND, elev_get_floor_sensor_signal());
    }
    return 0;
}

elev_motor_direction_t next_order(order_queue_t * self){
    if (self->head->request.floor > elev_get_floor_sensor_signal()){
        return DIRN_UP;
    }
    else if (self->head->request.floor < elev_get_floor_sensor_signal()){
        return DIRN_DOWN;
    }
    else {
        return DIRN_STOP;
    }
}

void complete_order(order_queue_t * self){
    clear_order(&self->head, elev_get_floor_sensor_signal());
}
