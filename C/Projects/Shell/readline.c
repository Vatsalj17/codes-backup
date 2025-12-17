#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main (void) {
    char *input;
    input = readline("write> ");
    printf("%s", input);
    free(input);
}
