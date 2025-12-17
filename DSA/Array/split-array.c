#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool sorted(int *arr, int n, int flag) {
    if (flag) {
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] >= arr[i + 1]) return false;
        }
    } else {
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] <= arr[i + 1]) return false;
        }
    }
    return true;
}

// long long splitArray(int* nums, int numsSize) {
//     long long min = INT_MAX;
//     for (int i = 1; i < numsSize; i++) {
//         long long sum1 = 0, sum2 = 0, diff = -1;
//         if ((!sorted(nums, i, 1)) || (!sorted(nums + i, numsSize - i, 0))) continue;
//         for (int j = 0; j < i; j++) sum1 += nums[j];
//         for (int j = i; j < numsSize; j++) sum2 += nums[j];
//         if (sum1 >= sum2) diff = sum1 - sum2;
//         else diff = sum2 - sum1;
//         if (diff < min) min = diff;
//     }
//     if (min == INT_MAX) return -1;
//     return min;
// }

long long splitArray(int* nums, int numsSize) {
    if (numsSize < 2)
        return -1;
    bool* inc = malloc(numsSize * sizeof(bool));
    bool* dec = malloc(numsSize * sizeof(bool));
    long long* prefix = malloc(numsSize * sizeof(long long));
    inc[0] = true;
    for (int i = 1; i < numsSize; i++) {
        inc[i] = inc[i - 1] && (nums[i - 1] < nums[i]);
    }
    dec[numsSize - 1] = true;
    for (int i = numsSize - 2; i >= 0; i--) {
        dec[i] = dec[i + 1] && (nums[i] > nums[i + 1]);
    }
    prefix[0] = nums[0];
    for (int i = 1; i < numsSize; i++) {
        prefix[i] = prefix[i - 1] + nums[i];
    }
    long long min = LLONG_MAX;
    for (int i = 1; i < numsSize; i++) {
        if (inc[i - 1] && dec[i]) {
            long long sum1 = prefix[i - 1];
            long long sum2 = prefix[numsSize - 1] - sum1;
            long long diff = llabs(sum1 - sum2);
            if (diff < min)
                min = diff;
        }
    }
    free(inc);
    free(dec);
    free(prefix);
    return (min == LLONG_MAX) ? -1 : min;
}

int main(void) {
    int arr[100];
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter arr: ");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    long long ans = splitArray(arr, n);
    printf("ans: %lld", ans);
}
