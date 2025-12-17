#ifndef STACK2_H
#define STACK2_H

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Stacks stack_s;

stack_s* stacks_init(size_t size);
bool pushs(stack_s* stack, const char* string);
char* pops(stack_s* stack);
char* peeks(stack_s* stack);
void destroys(stack_s* stack);
size_t size(stack_s* stack);

#endif
