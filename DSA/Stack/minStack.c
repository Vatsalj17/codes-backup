#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* values;
    int top;
    int min;
    int capacity;
} MinStack;

MinStack* minStackCreate() {
    MinStack* s = malloc(sizeof(MinStack));
    s->values = malloc(100 * sizeof(int));
    s->top = -1;
    s->min = INT_MAX;
    s->capacity = 100;
    return s;
}

bool stack_full(MinStack* stack) {
	return (size_t)stack->top >= stack->capacity - 1;
}

bool stack_empty(MinStack* stack) {
	return stack->top == -1;
}

void minStackPush(MinStack* obj, int val) {
	if (stack_full(obj)) {
		size_t new_capacity = obj->capacity * 2;
		int* temp = realloc(obj->values, new_capacity * sizeof(int));
		obj->capacity = new_capacity;
		obj->values = temp;
	}
	obj->top++;
	obj->values[obj->top] = val;
    if (val < obj->min) obj->min = val;
}

void minStackPop(MinStack* obj) {
    int val = obj->values[obj->top];
    int min = obj->values[0];
    for (int i = 1; i < obj->top; i++) {
        if (obj->values[i] < min) min = obj->values[i];
    }
    obj->min = min;
    if (obj->top == 0) min = INT_MAX;
    obj->top--;
}

int minStackTop(MinStack* obj) {
    return obj->values[obj->top];
}

int minStackGetMin(MinStack* obj) {
    return obj->min;
}

void minStackFree(MinStack* obj) {
    free(obj->values);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
