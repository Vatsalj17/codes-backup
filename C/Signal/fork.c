#include <signal.h>
#include <unistd.h>

int main() {
	signal(SIGCHLD, SIG_IGN);
	fork();
    sleep(3);
	fork();
    sleep(3);
	fork();
}
