#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    int fd = open("./text.txt", O_RDWR, S_IRUSR | S_IWUSR);
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("couldn't get file size\n");
        return EXIT_FAILURE;
    }
    printf("file size is %ld\n", sb.st_size);
    char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    for (int i = 0; i < sb.st_size; i++) {
        if (!isalpha(file_in_memory[i])) file_in_memory[i] = ' ';
    }
    printf("Buffer: \n%s\n", file_in_memory);
    close(fd);
}
