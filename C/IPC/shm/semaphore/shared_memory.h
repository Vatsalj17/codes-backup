#ifndef SH_MEMORY_H
#define SH_MEMORY_H

#include <stdbool.h>

#define BLOCK_SIZE 4096
#define FILENAME "writeshmem.c"

char* attack_memory_block(char* file, int size);
bool detach_memory_block(char* block);
bool destroy_memory_block(char* file);

// filename for two semaphores
#define SEM_PRODUCER_FNAME "/myproducer"
#define SEM_CONSUMER_FNAME "/myconsumer"

#endif
