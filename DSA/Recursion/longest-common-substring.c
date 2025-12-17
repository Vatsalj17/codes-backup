#include <stdio.h>
#include <string.h>

int lcs(char* str1, char* str2, int n, int m) {
	if (m == 0 || n == 0) return 0;
	if (str1[n - 1] == str2[m - 1]) {
		return 1 + lcs(str1, str2, n - 1, m - 1);
	} else {
		int a = lcs(str1, str2, n - 1, m);
		int b = lcs(str1, str2, n, m - 1);
		return (a > b) ? a : b;
	}
}

int main(void) {
	char str1[100], str2[100];
	printf("Enter the first string: ");
	fgets(str1, 100, stdin);
	int n = strlen(str1);
    str1[n - 1] = '\0';
	printf("Enter the second string: ");
	fgets(str2, 100, stdin);
	int m = strlen(str2);
    str2[m - 1] = '\0';
	printf("Answer: %d\n", lcs(str1, str2, strlen(str1), strlen(str2)));
}
