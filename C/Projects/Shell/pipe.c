#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd[2]; // file discriptor
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }
    int id = fork();
    if (id < 0) {
        perror("fork");
        return 4;
    }
    if (id == 0) {
        close(fd[0]); // child doesn't read
        int a;
        printf("Input a number: ");
        scanf("%d", &a);
        if (write(fd[1], &a, sizeof(int)) == -1) {
            perror("write");
            return 2;
        }
        close(fd[1]);
    } else {
        // firstly this is executed
        close(fd[1]); // parent doesn't write
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1) {
            perror("read");
            return 3;
        }
        y = y * 3;
        close(fd[0]);
        printf("Got form child process %d\n", y);
    }
}
