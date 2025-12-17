#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* myturn(void* args) {
    for (int i = 0; i < 8; i++) {
        sleep(1);
        printf("My turn!\n");
    }
    return NULL;
}

void* yourturn(void* args) {
    for (int i = 0; i < 3; i++) {
        sleep(2);
        printf("Your turn!\n");
    }
    return NULL;
}

int main() {
    pthread_t newthread;
    pthread_create(&newthread, NULL, myturn, NULL);
    yourturn(NULL);
    pthread_join(newthread, NULL);
    return 0;
}
