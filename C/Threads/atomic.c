#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

#define BIG 10000000UL

_Atomic uint64_t atomic_counter = 0;

void count_to_big() {
	for (int i = 0; i < BIG; i++) {
		atomic_counter += i;
        // atomic_counter = atomic_counter + i; // compiler can't handle it atomically
	}
}

void* threadfunc(void* arg) {
    count_to_big();
    return NULL;
}

int main(){
    pthread_t t1, t2;
    pthread_create(&t1, NULL, threadfunc, NULL);
    pthread_create(&t2, NULL, threadfunc, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("The result is %lu\n", atomic_counter);
    return 0;
}
