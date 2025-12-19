#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define QUEUE_EMPTY INT_MIN

typedef struct Queue queue_t;

queue_t* queue_init(size_t capacity);
bool queue_full(queue_t *queue);
bool queue_empty(queue_t *queue);
bool enqueue(queue_t *queue, int value);
int dequeue(queue_t *queue);
void queue_destroy(queue_t *queue);

#endif
