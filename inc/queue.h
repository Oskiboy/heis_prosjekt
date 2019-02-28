#ifndef QUEUE_T_H
#define QUEUE_T_H

#include <stdint.h>
#include <stdlib.h>

struct queue_struct_type;
typedef struct queue_struct_type queue_t; 

queue_t queue_create(size_t size);
int queue_free(queue_t* q);
int queue_push(queue_t* q, uint32_t data);
uint32_t queue_pop(queue_t* q);
size_t queue_size(queue_t* q);


#endif //QUEUE_T_H
