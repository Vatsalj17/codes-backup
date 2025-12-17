#include "shared_memory.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

static int get_shared_block(char* file, int size) {
    key_t key;
    key = ftok(file, 0);
    if (key == -1) return -1;

    return shmget(key, size, 0644 | IPC_CREAT); // create if doesn't exist
}

char* attack_memory_block(char* file, int size) {
    int block_id = get_shared_block(file, size);
    if (block_id == -1) return NULL;
    // map the shared block into the process's memory
    char* result = shmat(block_id, NULL, 0);
    if (result == (char*)-1) return NULL;
    return result;
}

bool detach_memory_block(char* block) {
    return shmdt(block) != -1;
}

bool destroy_memory_block(char* file) {
    int block_id = get_shared_block(file, 0);
    if (block_id == -1) return false;
    return shmctl(block_id, IPC_RMID, NULL) != -1;
}
