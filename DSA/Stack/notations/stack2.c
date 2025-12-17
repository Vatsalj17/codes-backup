#include "stack2.h"

#include <string.h>

typedef struct Stacks {
	char** str;
	int sp;
	size_t capacity;
} stack_s;

stack_s* stacks_init(size_t size) {
	stack_s* stack = malloc(sizeof(stack_s));
    stack->str = (char**)calloc(size, sizeof(char*));
    for (int i = 0; i < (int)size; i++) *stack->str = (char*)calloc(2 * size, sizeof(char));
	stack->sp = -1;
	stack->capacity = size;
	return stack;
}

bool is_empty(stack_s* stack) {
	if (stack->sp > -1) return false;
	return true;
}

bool is_full(stack_s* stack) {
	if (stack->sp >= (int)stack->capacity - 1) return true;
	return false;
}

bool pushs(stack_s* stack, const char* string) {
	if (stack == NULL || is_full(stack)) return false;
    stack->str[++stack->sp] = strdup(string);
	return true;
}

char* pops(stack_s* stack) {
	if (stack == NULL || is_empty(stack)) return NULL;
	char* value = stack->str[stack->sp];
    stack->sp--;
	return value;
}

char* peeks(stack_s* stack) {
	if (stack == NULL || is_empty(stack)) return NULL;
	return stack->str[stack->sp];
}

void destroys(stack_s* stack) {
    for (int i = 0; i < (int)stack->capacity; i++) free(stack->str[i]);
	free(stack->str);
	free(stack);
}

size_t size(stack_s* stack) {
    return stack->sp + 1;
}
