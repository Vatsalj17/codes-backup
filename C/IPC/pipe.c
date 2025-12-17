#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fds[2];
    int ret;
    if((ret = pipe(fds)) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    printf("0: %d\n", fds[0]);
    printf("1: %d\n", fds[1]);
    write(fds[1], "ajay\n", 5);
    char buf[10] = {0};
    read(fds[0], buf, 5);
    printf("%s", buf);
}
