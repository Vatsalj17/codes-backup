#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef union Header header_t;

void* malloc(size_t size);
void free(void* block);
void* calloc(size_t n, size_t size);
void* realloc(void* block, size_t size);

#endif
