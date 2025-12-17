#include "stack.h"
#include <string.h>

typedef struct Stack {
    char *data;
    int sp;
    size_t capacity;
} stack_t;

stack_t* stack_init(size_t size) {
    stack_t* stack = malloc(sizeof(stack_t));
    stack->data = calloc(size + 1, sizeof(char));
    stack->sp = -1;
    stack->capacity = size;
    return stack;
}

bool isEmpty(stack_t* stack) {
    if (stack->sp > -1) return false;
    return true;
}

bool isFull(stack_t* stack) {
    if (stack->sp >= (int)stack->capacity - 1) return true;
    return false;
}

bool push(stack_t* stack, char value) {
    if (stack == NULL || isFull(stack)) return false;
    stack->data[++stack->sp] = value;
    return true;
}

char pop(stack_t* stack) {
    if (stack == NULL || isEmpty(stack)) return EMPTY;
    char value = stack->data[stack->sp--];
    return value;
}

char peek(stack_t* stack) {
    if (stack == NULL || isEmpty(stack)) return EMPTY;
    return stack->data[stack->sp];
}

void destroy(stack_t* stack) {
    free(stack->data);
    free(stack);
}

char* get_string(stack_t* stack) {
    char* answer = strdup(stack->data);
    return answer;
}
