#include "../utils/mystd.h"

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void reverse(int* arr, int n) {
	for (int i = 0; i < n / 2; i++) swap(&arr[i], &arr[n - i - 1]);
}

void right_rotate(int* nums, int numsSize, int k) {
	int n = numsSize;
	k = k % n;
	// int idx = 0;
	// int* ans = malloc(n * sizeof(int));
	// for (int i = 0; i < n; i++) ans[(i + k) % n] = nums[i];
	// for (int i = 0; i < n; i++) nums[i] = ans[i];
    reverse(nums, n - k);
    reverse(nums + n - k, k);
    reverse(nums, n);
}

void left_rotate(int arr[], int n, int d) {
    reverse(arr, d);
    reverse(arr + d, n - d);
    reverse(arr, n);
}

int main(void) {
	int* nums;
	int n, k;
	getArr(&nums, &n);
	printf("Enter a number: ");
	scanf("%d", &k);
	left_rotate(nums, n, k);
	putArr(nums, n);
	free(nums);
}
