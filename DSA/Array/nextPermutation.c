#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int min(int *arr, int n, int pivot) {
    int min = arr[pivot + 1];
    int min_idx = pivot + 1;
    for (int i = pivot + 2; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            min_idx = i;
        }
    }
    return min_idx;
}

void reverse(int *arr, int n, int pivot) {
    int m = pivot;
    int mid = (n + m) / 2;
    int idx = 1;
    for (int i = m + 1; i <= mid; i++) {
        swap(&arr[i], &arr[n - idx]);
        idx++;
    }
}

void nextPermutation(int *nums, int numsSize) {
    int idx = numsSize - 1;
    while(idx > 0 && nums[idx] < nums[idx - 1]) idx--;
    printf("idx: %d\n", idx);
    if (idx > 0 && idx == numsSize - 1)
        swap(&nums[idx], &nums[idx - 1]);
    else if (idx == 0) reverse(nums, numsSize, -1);
    else {
        int pivot = idx - 1;
        int in = min(nums, numsSize, pivot);
        printf("in: %d\n", in);
        if (in != -1) swap(&nums[pivot], &nums[in]);
        // for (int i = pivot; i < numsSize; i++) {
        //     if (nums[i] == nums[pivot] + 1) {
        //         in = i;
        //         swap(&nums[pivot], &nums[i]);
        //         printf("pivot: %d, i: %d\n", pivot, i);
        //         break;
        //     }
        // }
        reverse(nums, numsSize, pivot);
    }
}

int main(void) {
    int n;
    int arr[100];
    printf("Enter length of array: ");
    scanf("%d", &n);
    printf("Enter the array: ");
    for (int i = 0; i < n; i++) {
        scanf(" %d", &arr[i]);
    }
    nextPermutation(arr, n);
    printf("The next perm: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
}
