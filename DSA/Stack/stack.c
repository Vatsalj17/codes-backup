#include "stack.h"
#include <stdio.h>

typedef struct Stack {
	int* values;
	int top;
	size_t capacity;
} stack_t;

stack_t* stack_init(size_t capacity) {
	stack_t* stack = malloc(sizeof(stack_t));
    if (stack == NULL) {
        perror("stack malloc failed");
        return NULL;
    }
	stack->capacity = capacity;
	stack->top = -1;
	stack->values = malloc(capacity * sizeof(int));
    if (stack->values == NULL) {
        perror("array malloc failed");
        free(stack);
        return NULL;
    }
	return stack;
}

bool stack_full(stack_t* stack) {
	return (size_t)stack->top >= stack->capacity - 1;
}

bool stack_empty(stack_t* stack) {
	return stack->top == -1;
}

bool push(stack_t* stack, int value) {
    if (stack == NULL) return false;
	if (stack_full(stack)) {
        size_t new_capacity = stack->capacity * 2;
		int* temp = realloc(stack->values, new_capacity * sizeof(int));
        if (temp == NULL) return false;
        stack->capacity = new_capacity;
        stack->values = temp;
	}
	stack->top++;
	stack->values[stack->top] = value;
	return true;
}

int pop(stack_t* stack) {
	if (stack == NULL || stack_empty(stack)) return STACK_EMPTY;
	int result = stack->values[stack->top--];
	return result;
}

void stack_destroy(stack_t* stack) {
    if (stack == NULL) return;
	free(stack->values);
	free(stack);
}
