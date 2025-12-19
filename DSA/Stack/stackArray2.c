#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_LENGTH 10
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

typedef struct {
    int values[STACK_LENGTH];
    int top;
} stack;

bool push(stack *myStack, int value) {
    if (myStack->top >= STACK_LENGTH - 1) return false;
    myStack->top++;
    myStack->values[myStack->top] = value;
    return true;
}

int pop(stack *myStack) {
    if (myStack->top == EMPTY) return STACK_EMPTY;
    int result = myStack->values[myStack->top--];
    return result;
}

int main(void) {
    stack s1, s2, s3;
    s1.top = EMPTY;
    s2.top = EMPTY;
    s3.top = EMPTY;
    int i = 0;
    while(push(&s1, i)) i++;
    while(push(&s2, i)) i++;
    while(push(&s3, i)) i++;

    int x, y, z;
    printf("s1 | s2 | s3\n");
    printf("------------\n");
    while((x = pop(&s1)) != STACK_EMPTY) {
        if ((y = pop(&s2)) == STACK_EMPTY) break;
        if ((z = pop(&s3)) == STACK_EMPTY) break;
        printf(" %d | %d | %d\n", x, y, z);
    }

    return 0;
}
