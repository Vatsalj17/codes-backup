#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
    * fd    streams

    * 0     stdin
    * 1     stdout
    * 2     stderr
    * 3     file by user
    * .
    * .
    * .
    * 1024
*/

int main(void) {
    char str[50];
    printf("stdin: ");
    fgets(str, 50, stdin);
    str[strlen(str) - 1] = '\0';

    int file = open("dump.txt", O_WRONLY | O_CREAT, 0777); // Last arg is for permission
    if (file == -1) return 2;
    printf("file discriptor(fd): %d\n", file);

    int file2 = dup2(file, STDOUT_FILENO);

    printf("the duplicated fd: %d\n", file2);
    printf("This is the input string: %s\n", str);

    close(file);
    printf("the file is closed\n");
}
