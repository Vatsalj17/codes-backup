#include "sort.h"

void swap(int *a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[low];
    int i = low, j = high;
    while (i < j) {
        while(arr[i] <= pivot && i < high) i++;
        while(arr[j] > pivot && j > low) j--;
        if (i < j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
		quick_sort(arr, low, pivot - 1);
		quick_sort(arr, pivot + 1, high);
    }
}
