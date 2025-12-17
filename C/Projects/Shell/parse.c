#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>

int main (void) {
    char *str = (char *)malloc(100 * sizeof(char));
    char *prompt = "write something: ";
    // printf("%s", prompt);
    // fgets(str, 100, stdin);
    // int size = strlen(str);
    // str[size - 1] = '\0';
    str = readline(prompt);
    printf("length of string: %ld\n", strlen(str));
    printf("The input string: %s\n", str);
	int bufsize = 64;
	char **tokens = malloc(bufsize * sizeof(char *));
	int index = 0;
    int pos = 0;
    while (str[pos] != '\0') {
        while (str[pos] == ' ') pos++;
        if (str[pos] == '\0') break;
        char *token = (char *)malloc(bufsize * sizeof(char));
        int i = 0;
        int count = 0;
        int check = false;
        while (check || (str[pos] != ' ' && str[pos] != '\0')) {
            if (str[pos] == '"') {
                check = !check;
                count++;
                pos++;
                if (count % 2 == 0) continue;
            }
            token[i++] = str[pos++];
        }
        token[i] = '\0';
        if (token[0] == '$') {
            char *tmp = malloc(128 * sizeof(char));
            tmp = getenv(token + 1);
            token = tmp;
        }
        tokens[index++] = token;
    }
	tokens[index] = NULL;
    int idx = 0;
    printf("Tokens:\n");
    while(tokens[idx] != NULL) {
        printf("%s\n", tokens[idx++]);
    }
}
