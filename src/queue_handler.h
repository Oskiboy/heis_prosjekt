#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include <stdbool.h>
#include "elev.h"

typedef struct request_struct request_t;
typedef struct order_queue_module_struct order_queue_t;

struct order_queue_module_struct {
    int (*check_for_order)(order_queue_t* self, elev_motor_direction_t direction);
    int (*update)(order_queue_t* self);
    void (*clear_queue)(order_queue_t* self);
    void (*complete_order)();
    elev_motor_direction_t (*next_order)(order_queue_t* self);
};

struct request_struct {
    int floor;
    elev_motor_direction_t direction;
};

#endif //QUEUE_HANDLER_H
