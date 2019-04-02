//
// Created by emil on 26.03.19.
//

#include "queueHandler.h"
#include <stdio.h>

node_t* init_list(request_t request){
    node_t * head = NULL;
    head = malloc(sizeof(node_t));
    head->request = request;
    head->next = NULL;
    return head;
}


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
            case DIRN_UP: printf("Up  ");
                break;
            case DIRN_DOWN: printf("Down");
                break;
            case DIRN_STOP: printf("Stop");
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

void remove_by_index(node_t **head, int n) {
    if (*head == NULL) {
        return;
    }

    int i = 0;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return;
        }
        current = current->next;
    }

    temp_node = current->next;
    current->next = temp_node->next;
    free(temp_node);


}

void delete_list(node_t ** head){
    while(*head != NULL) pop(head);
}


int check_for_order(node_t ** head, elev_motor_direction_t dir, int floor){
    int stop = 0;
    if (*head == NULL) {
        printf("STOP\n");
        return stop;
    }
    if((*head)->request.floor == floor){
        stop = 1;
    }


    node_t * current = *head;

    if (!stop) {

        while (current->next != NULL) {
            if (current->request.floor == floor &&
                (current->request.direction == dir || dir == DIRN_STOP || current->request.direction == DIRN_STOP)) {
                current = remove_node(head, &current);
                stop = 1;
            } else current = current->next;

        }

        if (current->request.floor == floor &&
            (current->request.direction == dir || dir == DIRN_STOP || current->request.direction == DIRN_STOP)) {
            stop = 1;
            remove_last(head);
        }
        if ((*head) == NULL) {
            return stop;
        }
    }

    current = *head;
    if(stop) {
        while (current->next != NULL) {
            if (current->request.floor == floor) {
                current = remove_node(head, &current);
            } else current = current->next;

        }

        if (current->request.floor == floor) {
            remove_last(head);
        }
        if (stop) printf("STOP\n");
        return stop;
    }
    return stop;
}