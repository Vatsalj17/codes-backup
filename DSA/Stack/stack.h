#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define STACK_EMPTY INT_MIN

typedef struct Stack stack_t;

stack_t* stack_init(size_t capacity);
bool stack_empty(stack_t* stack);
bool stack_full(stack_t *stack);
bool push(stack_t *stack, int value);
int pop(stack_t *stack);
void stack_destroy(stack_t *stack);

#endif
