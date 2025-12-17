#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool subset(int* arr, int n, int x) {
	if (x == 0) return true;
	if (n == 0) return false;
	if (arr[0] > x)
		return subset(arr + 1, n - 1, x);
	else
		return (subset(arr + 1, n - 1, x - arr[0]) || subset(arr + 1, n - 1, x));
}

int main(void) {
	int n;
	printf("Enter length: ");
	scanf("%d", &n);
	printf("Enter array: ");
	int* arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	printf("Enter x: ");
	int x;
	scanf("%d", &x);
	if (subset(arr, n, x))
		printf("True\n");
	else
		printf("False\n");
}
