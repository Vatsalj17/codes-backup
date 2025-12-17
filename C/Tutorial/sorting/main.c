#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main(void) {
	int n;
	printf("Enter the length of the array: ");
	scanf("%d", &n);
	int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter Array: ");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	// bubble_sort(arr, n);
	// selection_sort(arr, n);
	// insertion_sort(arr, n);
	// merge_sort(arr, 0, n - 1);
	// quick_sort(arr, 0, n - 1);
    radix_sort(arr, n);
	printf("Sorted array:\n");
	for (int j = 0; j < n; j++)
		printf("%d ", arr[j]);
	printf("\n");
	free(arr);
}
