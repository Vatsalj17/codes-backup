#include "queue.h"

#include <stdio.h>

typedef struct Queue {
	int* values;
	size_t head;
	size_t tail;
	size_t entries;
	size_t capacity;
} queue_t;

queue_t* queue_init(size_t capacity) {
	queue_t* queue = malloc(sizeof(queue_t));
	if (queue == NULL) {
		perror("queue malloc failed");
		return NULL;
	}
	queue->capacity = capacity;
	queue->head = 0;
	queue->tail = 0;
	queue->entries = 0;
	queue->values = malloc(capacity * sizeof(int));
	if (queue->values == NULL) {
		perror("array malloc failed");
        free(queue);
		return NULL;
	}
	return queue;
}

bool queue_full(queue_t* queue) {
	return queue->entries == queue->capacity;
}

bool queue_empty(queue_t* queue) {
	return queue->entries == 0;
}

bool enqueue(queue_t* queue, int value) {
	if (queue_full(queue)) return false;
	queue->values[queue->tail] = value;
    queue->tail = (queue->tail + 1) % queue->capacity;
	queue->entries++;
	return true;
}

int dequeue(queue_t* queue) {
	if (queue_empty(queue)) return QUEUE_EMPTY;
	int result = queue->values[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->entries--;
	return result;
}

void queue_destroy(queue_t* queue) {
	if (!queue) return;
	free(queue->values);
	free(queue);
}
