#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int sig) {
	const char msg[] = "Ahhh! SIGINT!\n";
	write(0, msg, sizeof(msg));
}

int main(void) {
	char s[200];
	struct sigaction sa = {
		.sa_handler = sigint_handler,
		.sa_flags = SA_RESTART,
		.sa_mask = 0,
	};

	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("Enter a string: ");

	if (fgets(s, sizeof s, stdin) == NULL)
		perror("fgets");
	else
		printf("You entered: %s\n", s);

	return 0;
}
