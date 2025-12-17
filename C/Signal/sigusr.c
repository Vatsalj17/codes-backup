#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t got_usr1;

void sigusr1_handler(int sig) {
	(void)sig;
	got_usr1 = 1;
}

void sigint_handler(int sig) {
	const char msg[] = "Ahhh! SIGINT!\n";
	write(0, msg, sizeof(msg));
}

int main(void) {
	struct sigaction sa = {
		.sa_handler = sigusr1_handler,
		.sa_flags = SA_RESTART,
	};
	struct sigaction sa2 = {
		.sa_handler = sigint_handler,
		.sa_flags = SA_RESTART,
	};
	if (sigaction(SIGINT, &sa2, NULL) == -1) {
		perror("sigaction, sigint");
		exit(1);
	}
	got_usr1 = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		perror("sigaction, sigusr");
		exit(1);
	}
	while (!got_usr1) {
		printf("PID %d: working hard...\n", getpid());
		sleep(1);
	}
	printf("Done in by SIGUSR1!\n");
	return 0;
}
