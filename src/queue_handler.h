#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include <stdbool.h>

typedef enum {
    INT_1,
    INT_2,
    INT_3,
    EXT_1_U,
    EXT_2_U,
    EXT_3_U,
    EXT_4_D,
    EXT_3_D,
    EXT_2_D,
    ORDER_N
}order_type_t;

typedef struct {
    bool active;
} order_t;


#endif //QUEUE_HANDLER_H
