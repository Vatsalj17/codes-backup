#include "../utils/mystd.hpp"
#include <stdbool.h>

bool checkSorted(vector<int> &nums) {
    int n = nums.size();
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
    vector<int> nums;
    getVec(nums);
    cout << "Ans: " << checkSorted(nums) << endl;
}
