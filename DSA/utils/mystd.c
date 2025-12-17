#include "mystd.h"

void getArr(int** arr, int* n) {
	printf("Enter length of array: ");
	scanf("%d", n);
	*arr = (int*)malloc(*n * sizeof(int));
	if (*arr == NULL) {
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return;
	}
	printf("Enter array elements: ");
	for (int i = 0; i < *n; i++) {
		scanf("%d", &(*arr)[i]);
	}
}

void putArr(const int* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
