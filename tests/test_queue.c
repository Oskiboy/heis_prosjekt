#include "unity.h"
#include <stdio.h>
#include "queue_handler.h"
#include <stdlib.h>
#include <time.h>

void test_some_thing_to_test(void) {
    printf("\n");
    srand(time(NULL));

    node_t* queue = NULL;
    int stamp = 0;
    for(int i = 0; i < 200; i++) {
        request_t req;
        req.floor = rand()%4;
        if (req.floor ==0) req.direction = rand()%2;
        else if (req.floor ==3) req.direction = rand()%2 -1;
        else req.direction = rand()%3-1;
        req.stamp = stamp;
        stamp++;
        push(&queue, req);
    }

    /*
    print_list(queue);
    delete_list(queue);
    print_list((queue));
    check_for_order(&queue, 0, 1);
    print_list(queue);
    */

    elev_motor_direction_t dir = DIRN_STOP;
    int floor = 0;
    int next_floor = queue->request.floor;


    int n = 0;
    while(1) {
        //print_list(queue);
        printf("\nn: %d  floor: %d  next_floor: %d  dir: %d\n",n, floor, next_floor, (int)dir);
        check_for_order(&queue, dir, floor);
        print_list(queue);

        if (queue == NULL) {
            //printf("waiting\n");
            dir = 0;
        }
        else {
            next_floor = queue->request.floor;
            if (next_floor > floor)dir = DIRN_UP;
            else dir = DIRN_DOWN;
        }

        if (dir == DIRN_UP) floor += 1;
        if (dir == DIRN_DOWN) floor -= 1;

        if(rand()%5 == 0) {
            printf("\nnew stuff\n");

            while (rand()%3 != 0) {

                request_t req;
                req.floor = rand() % 4;
                if (req.floor == 0) req.direction = rand() % 2;
                else if (req.floor == 3) req.direction = rand() % 2 - 1;
                else req.direction = rand() % 3 - 1;
                req.stamp = stamp;
                stamp++;

                push(&queue, req);
            }
            print_list(queue);

        }
        n++;
        if (n>10) break;
    }

    //remove_by_index(&queue, 2);
    //print_list(queue);
    delete_list(&queue);
}


int main() {
    UNITY_BEGIN();
    return UNITY_END();
}