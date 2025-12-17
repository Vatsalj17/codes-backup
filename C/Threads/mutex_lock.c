#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BIG 10000000UL
pthread_mutex_t lock;

uint64_t counter = 0;

void count_to_big() {
	for (int i = 0; i < BIG; i++) {
		pthread_mutex_lock(&lock);
		counter += i;
		pthread_mutex_unlock(&lock);
	}
}

void* threadfunc(void* arg) {
	count_to_big();
	return NULL;
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, NULL, threadfunc, NULL);
	pthread_create(&t2, NULL, threadfunc, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("The result is %lu\n", counter);
	return 0;
}
