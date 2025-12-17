#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared_memory.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: %s [text to write]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* block = attack_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        printf("block: Couldn't find file\n");
        return -1;
    }

    printf("Writing \"%s\"\n", argv[1]);
    strncpy(block, argv[1], BLOCK_SIZE);

    detach_memory_block(block);
    return 0;
}
