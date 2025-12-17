#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_EMPTY INT_MIN

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct {
    node *head;
    node *tail;
} queue;

void init_queue(queue *q) {
    q->head = NULL;
    q->tail = NULL;
}

bool enqueue(queue *q, int value) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->next = NULL;
    if (q->tail != NULL) q->tail->next = newNode; // if not empty
    q->tail = newNode; // there's new tail now
    if (q->head == NULL) q->head = newNode; // if empty
    return true;
}

int dequeue(queue *q) {
    if (q->head == NULL) return QUEUE_EMPTY;
    node *temp = q->head;
    int value = temp->value;
    q->head = q->head->next;
    if (q->head == NULL) q->tail = NULL;
    free(temp);
    return value;
}

int main(void) {
    queue q;
    init_queue(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    int i;
    while((i = dequeue(&q)) != QUEUE_EMPTY) {
        printf("%d\n", i);
    }
}
