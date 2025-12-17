#include "sort.h"

void insertion_sort(int *arr, int n) {
	for (int i = 1; i < n; i++) {
		int current = arr[i];
		int prev = i - 1;
		while (arr[prev] > current && prev >= 0) {
			arr[prev + 1] = arr[prev];
			prev--;
		}
		arr[prev + 1] = current;
	}
}

