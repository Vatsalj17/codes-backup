#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lps(char* str, int n) {
    if (n <= 1) return 1;
    if (str[0] == str[n - 1]) {
        return 1 + lps(str + 1, n - 1);
    } else {
        int a = lps(str + 1, n);
        int b = lps(str, n - 1);
        return (a > b)? a : b;
    }
}

int main(void) {
	char *str = calloc(100, sizeof(char));
	printf("Enter the first string: ");
	fgets(str, 100, stdin);
	int n = strlen(str);
    str[n - 1] = '\0';
    printf("%s\n", str);
	printf("Answer: %d\n", lps(str, strlen(str)));
}
