#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void subset(int* arr, int n, int* out, int i, int x) {
	if (x == 0) {
		for (int j = 0; j < i; j++) printf("%d, ", out[j]);
		printf("\n");
		return;
	}
	if (n == 0) return;
	subset(arr + 1, n - 1, out, i, x);
	out[i] = arr[0];
	i++;
	subset(arr + 1, n - 1, out, i, x - arr[0]);
	i--;
}

int count(int* coins, int n, int sum) {
	if (sum == 0) return 1;
	if (sum < 0) return 0;
	if (n <= 0) return 0;
	return count(coins, n - 1, sum) + count(coins, n, sum - coins[n - 1]);
}

int main(void) {
	int n;
	printf("Enter length: ");
	scanf("%d", &n);
	printf("Enter array: ");
	int* arr = malloc(n * sizeof(int));
	int* out = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	printf("Enter x: ");
	int x;
	scanf("%d", &x);
	subset(arr, n, out, 0, x);
    printf("Count: %d", count(arr, n, x));
	free(arr);
	free(out);
}
