#include <stdio.h>

int main(void) {
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);
    if (!(n & 1)) return 1;
	int st = n + 1, sp = -1;
	for (int i = 1; i <= n; i++) {
		if (i == 1 || i == n) {
			for (int j = 1; j <= n; j++) {
				printf("*");
			}
			printf("\n");
		} else {
			for (int j = 1; j <= st / 2; j++) {
				printf("*");
			}
			for (int j = 1; j <= sp; j++) {
				printf(" ");
			}
			for (int j = 1; j <= st / 2; j++) {
				printf("*");
			}
			printf("\n");
		}
		if (i <= n / 2) {
			st -= 2;
			sp += 2;
		} else {
			st += 2;
			sp -= 2;
		}
	}
}
