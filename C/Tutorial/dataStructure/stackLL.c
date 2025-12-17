#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define STACK_EMPTY INT_MIN

typedef struct node {
    int value;
    struct node *next;
} node;

node *head = NULL;

bool push(int value) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) return false;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
    return true;
}

int pop() {
    if (head == NULL) return STACK_EMPTY;
    int value = head->value;
    node *temp = head;
    head = head->next;
    free(temp);
    return value;
}

int main(void) {
    push(56);
    push(79);
    push(12);
    push(-34);

    int i;
    while((i = pop()) != STACK_EMPTY) printf("%d\n", i);

    return 0;
}
