#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define QUEUE_LENGTH 10
#define EMPTY (-1)
#define QUEUE_EMPTY INT_MIN

typedef struct {
    int values[QUEUE_LENGTH];
    int head;
    int tail;
} queue;

bool isFull(queue *myQueue) {
    return myQueue->tail >= QUEUE_LENGTH - 1;
}

bool isEmpty(queue *myQueue) {
    return myQueue->head == EMPTY || myQueue->head > myQueue->tail;
}

bool enqueue(queue *myQueue, int value) {
    if (isFull(myQueue)) return false;
    if (isEmpty(myQueue)) myQueue->head = 0; // if queue is empty
    myQueue->tail++;
    myQueue->values[myQueue->tail] = value;
    return true;
}

int dequeue(queue *myQueue) {
    if (isEmpty(myQueue)) return QUEUE_EMPTY;
    int result = myQueue->values[myQueue->head++];
    return result;
}

int main(void) {
    queue q1, q2, q3;
    q1.head = EMPTY;
    q1.tail = EMPTY;
    q2.head = EMPTY;
    q2.tail = EMPTY;
    q3.head = EMPTY;
    q3.tail = EMPTY;
    int i = 0;
    while(enqueue(&q1, i)) i++;
    while(enqueue(&q2, i)) i++;
    while(enqueue(&q3, i)) i++;

    int x, y, z;
    printf("q1 | q2 | q3\n");
    printf("------------\n");
    while((x = dequeue(&q1)) != QUEUE_EMPTY) {
        if ((y = dequeue(&q2)) == QUEUE_EMPTY) break;
        if ((z = dequeue(&q3)) == QUEUE_EMPTY) break;
        printf(" %d | %d | %d\n", x, y, z);
    }

    return 0;
}
