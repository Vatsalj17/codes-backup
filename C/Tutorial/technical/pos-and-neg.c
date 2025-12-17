#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void shiftAndInsert

void alternate(int* arr, int n) {
	bool positive = false;
	if (arr[0] < 0) positive = true;
	int fromIdx = 1;
	for (int i = 1; i < n; i++) {
		if (positive) {
			if (arr[i] >= 0) {
				if (fromIdx != i) {
					shiftAndInsert(arr, fromIdx, i);
					i = fromIdx;
				}
				positive = false;
				fromIdx = i + 1;
			}
		} else {
			if (arr[i] < 0) {
				if (fromIdx != i) {
					shiftAndInsert(arr, fromIdx, i);
					i = fromIdx;
				}
				positive = true;
				fromIdx = i + 1;
			}
		}
	}
}

int main(void) {
	int n;
	printf("Enter size: ");
	scanf("%d", &n);
	int *arr = malloc(n * sizeof(int));
    printf("Enter array: ");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    alternate(arr, n);
}
