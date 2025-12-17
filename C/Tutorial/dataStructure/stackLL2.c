#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define STACK_EMPTY INT_MIN

typedef struct node {
    int value;
    struct node *next;
} node;

typedef node* stack_ptr;

bool push(stack_ptr *myStack, int value) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) return false;
    newNode->value = value;
    newNode->next = *myStack;
    *myStack = newNode;
    return true;
}

int pop(stack_ptr *myStack) {
    if (*myStack == NULL) return STACK_EMPTY;
    int value = (*myStack)->value;
    node *temp = *myStack;
    *myStack = (*myStack)->next;
    free(temp);
    return value;
}

void destroy_stack(stack_ptr *myStack) {
    node *current = *myStack;
    node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *myStack = NULL;
}

int main(void) {
    stack_ptr s1 = NULL, s2 = NULL, s3 = NULL;
    push(&s1, 56);
    push(&s1, 34);
    push(&s1, 12);

    push(&s2, -79);
    push(&s2, 34);
    push(&s2, -11);
    push(&s2, -85);

    push(&s3, 12);

    int i;
    while((i = pop(&s2)) != STACK_EMPTY) printf("%d\n", i);

    destroy_stack(&s1);
    destroy_stack(&s2);
    destroy_stack(&s3);
    return 0;
}
