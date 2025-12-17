#include <stdio.h>
#include "shared_memory.h"

int main(void) {
    if (destroy_memory_block(FILENAME)) {
        printf("Destroyed block: %s\n", FILENAME);
    } else {
        printf("Couldn't destroy block: %s\n", FILENAME);
    }
}
