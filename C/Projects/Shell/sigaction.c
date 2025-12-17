#include <signal.h>
#include <unistd.h>

void sigint_handler(int signo) {
    write(1, "Caught sig\n", 12);
}

int main () {
    // signal(SIGINT, sigint_handler);
    struct sigaction s;
    s.sa_handler = sigint_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s, NULL);
    while(1);
}
