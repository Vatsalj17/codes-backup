#include "sort.h"

int get_max_element(int* arr, int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

void counting_sort(int* arr, int n, int place) {
	int output[n];
	int count[10] = {0};

    // count digit occurance
	for (int i = 0; i < n; i++) 
        count[(arr[i] / place) % 10]++;

    // change count[i] so that count[i] now contains actual position of this digit in output array
	for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--)
		output[--count[(arr[i] / place) % 10]] = arr[i];

	for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radix_sort(int* arr, int n) {
	int max = get_max_element(arr, n);
	for (int place = 1; max / place > 0; place *= 10)
		counting_sort(arr, n, place);
}
