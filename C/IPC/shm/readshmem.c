#include <stdio.h>
#include <stdlib.h>
#include "shared_memory.h"

int main(void) {
    char* block = attack_memory_block(FILENAME, BLOCK_SIZE);
    if (!block) {
        printf("block: couldn't get block\n");
        return EXIT_FAILURE;
    }
    printf("Reading: \"%s\"\n", block);
    detach_memory_block(block);
}
