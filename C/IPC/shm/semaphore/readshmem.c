#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include "shared_memory.h"

int main(void) {
    sem_unlink(SEM_CONSUMER_FNAME);
    sem_unlink(SEM_PRODUCER_FNAME);

    sem_t *sem_prod = sem_open(SEM_PRODUCER_FNAME, O_CREAT, 0660, 0);
    if (sem_prod == SEM_FAILED) {
        perror("sem-open/producer");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_cons = sem_open(SEM_CONSUMER_FNAME, O_CREAT, 0660, 1);
    if (sem_cons == SEM_FAILED) {
        perror("sem-open/consumer");
        exit(EXIT_FAILURE);
    }

    char* block = attack_memory_block(FILENAME, BLOCK_SIZE);
    if (!block) {
        printf("block: couldn't get block\n");
        return EXIT_FAILURE;
    }

    while(true) {
        sem_wait(sem_prod);
        if (strlen(block) > 0) {
            printf("Reading: \"%s\"\n", block);
            bool done = (strcmp(block, "quit") == 0);
            block[0] = 0;
            if (done) break;
        }
        sem_post(sem_cons);
    }
    sem_close(sem_prod);
    sem_close(sem_cons);
    detach_memory_block(block);
}
