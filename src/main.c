#include <stdio.h>
#include "fsm.h"
#include "queue_handler.h"

FSM_MODULE(fsm_m);
QUEUE_MODULE(queue_m);

int main() {
    printf("Elevator starting...\n");
    run_fsm(&fsm_m, &queue_m);
    printf("Elevator stopping!\n");
    return 0;
}
