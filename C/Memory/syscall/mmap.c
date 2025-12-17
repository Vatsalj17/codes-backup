#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

// #define PAGESIZE 0x1000
#define PAGESIZE 4096

int main(void) {
	uint8_t* first = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	uint8_t* second = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    printf("First: %p\n", first); 
    printf("Second: %p\n", second); 
}
