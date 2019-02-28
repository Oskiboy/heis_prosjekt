#include "queue.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define NULL_ERROR          (-2)
#define QUEUE_ERROR         (-1)

struct queue_struct_type {
    uint32_t*   base;
    uint32_t*   front;
    uint32_t*   back;
    size_t      size;
    size_t      max_size;
};


/**
 * @brief Create a queue of a certain size
 * 
 * @param size The maximum size of the queue
 * @return queue_t The newly created que object.
 */
queue_t queue_create(size_t size) {
    queue_t q;
    q.base = malloc(size * sizeof(uint32_t));
    if(!q.base) {
        fprintf(stderr, "ERROR - queue could not be allocated\n");
        exit(NULL_ERROR);  //Malloc error
    }

    q.size = 0;
    q.max_size = size;
    q.front = q.base;
    q.back = q.base;

    return q;
}

/**
 * @brief Frees the memory allocated by the queue, must be called before queue object goes out of scope
 * 
 * @param q Queue to be freed.
 * @return int Success(0), failure(-2)
 */
int queue_free(queue_t* q) {
    if(!q || !q->base) {
        return NULL_ERROR;  //NULL shit
    }
    free(q->base);
    q->base = NULL;
    return 0;
}

/**
 * @brief Add a data element to the queue
 * 
 * @param q Pointer to your queue
 * @param data Data you want pushed
 * @return int Success(0) or fail(-1)
 */
int queue_push(queue_t* q, uint32_t data) {
    if(!q || !q->base)        
        return NULL_ERROR;  //Malloc error

    ///TODO: What happens if the queue doesn't wrap around
    if(q->size >= q->max_size) {
        q->base = realloc(q->base, 2 * q->max_size);
    }

    ///TODO: If the queue is full, it should wrap around.
    q->back++;
    q->back = data;

    q->size++;
    return 0;
}


/**
 * @brief Pop off the head of the queue and return its value
 * 
 * @param q The queue to be popped
 * @return uint32_t Data that has been popped of the queue
 */
uint32_t queue_pop(queue_t* q) {
    uint32_t data;
    if(!q || !q->base)
        return NULL_ERROR;

    if(!q->size)
        return QUEUE_ERROR; //Queue is empty
    
    //Save the queue element and increment the front of the queue
    data = *q->front++;

    //If the queue is empty, move front and back to the base of the array.
    if(q->front == q->back) {
        q->front = q->base;
        q->back = q->base;
    }

    q->size--;

    return data;
}


/**
 * @brief Return the size of the queue
 * 
 * @param q Object whos size is being checked
 * @return size_t The size of the queue
 */
size_t queue_size(queue_t* q) {
    if(!q || !q->base) {
        return NULL_ERROR;
    }
    return q->size;
}