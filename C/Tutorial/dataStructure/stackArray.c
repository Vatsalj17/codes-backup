#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_LENGTH 10
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

int myStack[STACK_LENGTH];
int top = EMPTY;

bool push(int value) {
    if (top >= STACK_LENGTH - 1) return false;
    top++;
    myStack[top] = value;
    return true;
}

int pop() {
    if (top == EMPTY) return STACK_EMPTY;
    int result = myStack[top--];
    return result;
}

int main(void) {
    int i = 0;
    while(push(i)) i++;

    while((i = pop()) != STACK_EMPTY) printf("%d\n", i);

    return 0;
}
