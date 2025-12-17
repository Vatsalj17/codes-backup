#include <signal.h>
#include <unistd.h>

void sigint_handler(int signo) {
    write(1, "Caught sig\n", 13);
}

int main () {
    // signal(SIGINT, sigint_handler);
    signal(SIGINT, SIG_IGN);
    while(1);
}
