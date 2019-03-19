#include "queue_handler.h"

static int next_floor = INT_1;
static order_t order_array[ORDER_N];

int get_next_floor() {
    return next_floor;
}

void add_order(order_type_t order) {
    order_array[order].active = true;

}

void complete_current_order() {
    order_array[next_floor].active = false;
    calculate_next_floor();
}

void clear_orders() {
    for(int i = 0; i < ORDER_N; i++) {
        order_array[i].active = false;
    }
}

void init_order_handler() {
    clear_orders();

}

void calculate_next_floor() {

}

void find_order_score(order_type_t order) {

}
