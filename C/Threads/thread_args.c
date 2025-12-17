#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* myturn(void* args) {
    int *iptr = (int *)args;
    for (int i = 0; i < 8; i++) {
        sleep(1);
        printf("My turn! %d %d\n", i, *iptr);
        (*iptr)++;
    }
    return NULL;
}

void* yourturn(void* args) {
    for (int i = 0; i < 3; i++) {
        sleep(2);
        printf("Your turn! %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t newthread;
    int v = 10;
    pthread_create(&newthread, NULL, myturn, &v);
    yourturn(NULL);
    pthread_join(newthread, NULL);
    printf("Threads done: %d\n", v);
    return 0;
}
