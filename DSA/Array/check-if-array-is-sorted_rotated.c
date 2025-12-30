#include "../utils/mystd.h"
#include <stdbool.h>

bool checkSorted(int* nums, int numsSize) {
    int n = numsSize;
    int check = 0;
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] > nums[i + 1]) check++;
    }
    if (check > 1) return false;
    else if (check == 1) {
        if (nums[0] <= nums[n - 1]) return false;
        else return true;
    } else return true;
}

int main(void) {
    int* nums, n;
    getArr(&nums, &n);
    printf("Ans: %d\n", checkSorted(nums, n));
}
