#include "sort.h"

void bubble_sort(int *arr, int n) {
	int temp;
	for (int i = n; i > 1; i--) {
		for (int j = 0; j < i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

