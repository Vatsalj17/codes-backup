#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define EMPTY CHAR_MAX

typedef struct Stack stack_t;

stack_t* stack_init(size_t size);
bool push(stack_t* stack, char value);
char pop(stack_t* stack);
char peek(stack_t* stack);
bool isEmpty(stack_t* stack);
void destroy(stack_t* stack);
char* get_string(stack_t* stack);

#endif
