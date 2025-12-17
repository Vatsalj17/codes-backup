#include <stdio.h>
#include <string.h>

int countFlips(char* str, int k) {
	int flips = 0, i = 0;
	unsigned long n = strlen(str) - k;
	for (; i <= n; i++) {
		if (str[i] == '0') {
			for (int j = 0; j < k; j++) str[j + i] = (str[j + i] == '0') ? '1' : '0';
			flips++;
		}
	}
	while (str[++n] != '\0')
		if (str[i] == '0') return -1;
	return flips;
}

int main(void) {
	char* bits;
	printf("Enter the string of bits: ");
	scanf("%s", bits);
	int k;
	printf("Enter k: ");
	scanf("%d", &k);
}
