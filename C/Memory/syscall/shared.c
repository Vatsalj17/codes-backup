#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define PAGESIZE 4096

int v = 5;

int main(int argc, char** argv) {
    int *shared_memory = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared_memory = 14;
    if (fork() == 0) {
        v = 80;
        *shared_memory = 92;
    } else {
        wait(NULL);
    }
    printf("Not shared. %i\n", v);
    printf("Shared. %i\n", *shared_memory);
}
