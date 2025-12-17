#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool sorted(int *arr, int n) {
	for (int k = 1; k < n; k++) {
		if (arr[k] < arr[k - 1]) {
			return false;
		}
	}
	return true;
}

int linear_search(int *arr, int n, int s) {
	for (int i = 0; i < n; i++) if (arr[i] == s) return i;
	return -1;
}

int binary_search(int *arr, int n, int s) {
	int end = n - 1, beg = 0;
	while (end >= beg) {
		int mid = (beg + end) / 2;
		if (s == arr[mid])
			return mid;
		else if (s > arr[mid])
			beg = mid + 1;
		else
			end = mid - 1;
	}
	return -1;
}

int main(void) {
	int n, s, index;
	printf("Enter the length of the array: ");
	scanf("%d", &n);
	int *arr = (int *)malloc(n * sizeof(int));
	printf("Enter the array:\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	printf("Enter the searching element: ");
	scanf("%d", &s);
	if (sorted(arr, n))
		index = binary_search(arr, n, s);
	else
		index = linear_search(arr, n, s);
	if (index == -1)
		printf("Not found");
	else
		printf("%d is found at index %d", s, index);
}
