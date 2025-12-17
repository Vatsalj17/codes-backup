#include <stdlib.h>
#include "sort.h"

void merge(int *arr, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *leftArr = malloc(n1 * sizeof(int));
	int *rightArr = malloc(n2 * sizeof(int));

	for (int i = 0; i < n1; i++)
		leftArr[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		rightArr[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
        arr[k++] = leftArr[i++];
    while (j < n2)
        arr[k++] = rightArr[j++];

	free(leftArr);
	free(rightArr);
}

void merge_sort(int *arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
