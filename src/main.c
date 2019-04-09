#include <stdio.h>
#include "fsm.h"
#include "queue_handler.h"
#include "elev.h"

FSM_MODULE(fsm_m);
QUEUE_MODULE(queue_m);

int main() {
    elev_init();
    printf("Elevator starting...\n");
    run_fsm(&fsm_m, &queue_m);
    printf("Elevator stopping!\n");
    return 0;
}
