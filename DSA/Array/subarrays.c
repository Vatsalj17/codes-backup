#include "../utils/mystd.h"

int **generateSubarrays(int *arr, int n, int *count) {
    int total = (n * (n + 1)) / 2;
    *count = total;
    int **subarrays = malloc(total * sizeof(int*));
    
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int len = j - i + 1;
            subarrays[idx] = malloc(len * sizeof(int));
            int x = 0;
            for (int k = i; k <= j; k++) subarrays[idx][x++] = arr[k];
            idx++;
        }
    }

    return subarrays;
}

int main(void) {
    int *arr, n, count;
    getArr(&arr, &n);
    int **subarrays = generateSubarrays(arr, n, &count);
    int idx = 0;
    for (int i = 0; i < n * n; i++) {
        for (int j = i; j < n; j++) {
            int len = j - i + 1;
            putArr(subarrays[idx++], len);
        }
    }
    for (int i = 0; i < count; i++) free(subarrays[i]);
    free(subarrays);
}
