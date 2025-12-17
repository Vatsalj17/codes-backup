#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 10

char buffer[BUFSIZE]  = "message";
char password[BUFSIZE] = "passwd";

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <password> <message>\n", argv[0]);
        return EXIT_FAILURE;
    }
    strcpy(buffer, argv[2]);
    if (strcmp(password, argv[1])) {
        printf("Wrong password\n");
    } else {
        printf("Correct password\n");
        printf("msg: %s\n", buffer);
    }
    return EXIT_SUCCESS;
}
