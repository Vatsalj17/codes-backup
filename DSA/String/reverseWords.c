#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverseWords(char *s) {
    int n = strlen(s) + 1;
    char *ans = (char *)malloc(n * sizeof(char));
    char **tokens = malloc(n * sizeof(char *));
    char *token;
    int idx = 0;
    token = strtok(s, " ");
    while (token != NULL) {
        tokens[idx++] = token;
        token = strtok(NULL, " ");
    }
    tokens[idx - 1][strlen(tokens[idx - 1]) - 1] = '\0';
    int pos = 0;
    for (int i = idx - 1; i >= 0; i--) {
        int len = strlen(tokens[i]);
        memcpy(ans + pos, tokens[i], len);
        pos += len;
        if (i > 0) ans[pos++] = ' ';
    }
    ans[pos] = '\0';
    free(tokens);
    return ans;
}

int main() {
    char s[100];
    printf("Enter the string: ");
    fgets(s, 100, stdin);
    char *ans = reverseWords(s);
    puts(ans);
    free(ans);
}
