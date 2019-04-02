#include <stdio.h>
#include "queue_handler.h"
#include <stdlib.h>
#include <time.h>

int main() {
    printf("\n");
    srand(time(NULL));
    printf("hello\n\n");

    node_t* queue = NULL;

    int stamp = 0;
    for(int i = 0; i < 20; i++) {
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
    check_for_order(&queue, 0, 1);
    print_list(queue);


    node_t * current;
    current = (queue);
    while (queue != NULL) {
        pop(&queue);
    }
    printf("\n");
    print_list(queue);

*/

    elev_motor_direction_t dir = DIRN_STOP;
    int floor = 0;
    int next_floor = queue->request.floor;


    int n = 0;
    while(1) {
        printf("\nn: %d  floor: %d  next_floor: %d  dir: %d\n",n, floor, next_floor, (int)dir);

        if (check_for_order(&queue, dir, floor)){
            complete_order(&queue, floor);
        }
        print_list(queue);

        if (queue == NULL) {
            printf("waiting\n");
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
            printf("\nnew stuff");

            for (int i = 0; i < 2; i++) {

                request_t req;
                req.floor = rand() % 4;
                if (req.floor == 0) req.direction = rand() % 2;
                else if (req.floor == 3) req.direction = rand() % 2 - 1;
                else req.direction = rand() % 3 - 1;
                req.stamp = stamp;
                stamp++;

                push(&queue, req);
            }
        }
        n++;
        if (n>1) break;
    }





    //remove_by_index(&queue, 2);
    //print_list(queue);
    delete_list(&queue);
    return 0;
}
