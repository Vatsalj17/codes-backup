#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char env[10];
    printf("Enter the variable: ");
    fgets(env, 10, stdin);
    env[strlen(env) - 1] = '\0';
    char *val = getenv(env);
    printf("%s = %s\n", env, val);
}
