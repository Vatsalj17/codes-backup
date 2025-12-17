#include <stdio.h>
#include <string.h>
#include <errno.h>

extern int errno;

int main (void) {
    printf("Errno before: %d\n", errno);
    FILE *fh = fopen("nothing.txt", "r");
    if (fh == NULL) {
        printf("Errno after: %d\n", errno);

        printf("Err msg: %s\n", strerror(errno));
        // or
        perror("Err msg");

    } else fclose(fh);
}
