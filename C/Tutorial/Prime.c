#include <stdio.h>
// this is nano
int main() {
	int i, f;
	int swit = 0;
	printf("Enter initial number(>1): ");
	scanf("%d", &i);
	printf("Enter final number: ");
	scanf("%d", &f);
	if (f >= i && i >= 2) {
		printf("All prime nubers from %d to ", i);
		printf("%d are\n", f);
		for (int n = i; n <= f; n++) {
			for (int k = 2; k <= n / 2; k++) {
				if (n % k == 0) {
					swit++;
					break;
				}
			}
			if (swit == 0) {
				printf("%d\n", n);
			} else {
				swit = swit - 1;
			}
		}
	} else {
		printf("error\n");
	}
	return 0;
}
