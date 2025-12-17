#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_NAME "american_maid"

int main(void) {
	char s[300];
	int num, fd;
	mkfifo(FIFO_NAME, 0644);
	printf("waiting for readers...\n");
	fd = open(FIFO_NAME, O_WRONLY);
	printf("got a reader--type some stuff\n");
	while (fgets(s, 300, stdin), !feof(stdin)) {
		if ((num = write(fd, s, strlen(s))) == -1)
			perror("write");
		else if (num == 1)
			break;
		else
			printf("speak: wrote %d bytes\n", num);
	}
	return 0;
}
