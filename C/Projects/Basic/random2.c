#include <stdio.h>
#include <unistd.h>

unsigned int lcg(unsigned int *seed) {
    *seed = (*seed * 1103515245 + 12345) & 0x7fffffff; 
    return (*seed / 65536) % 10000; 
}

int main(void) {
    unsigned int seed = 9383; 
    for (int i = 0; 1 ; i++) {
        printf("%u\n", lcg(&seed));
        sleep(1);
    }
    return 0;
}
