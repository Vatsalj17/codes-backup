#include "../utils/mystd.hpp"

int main(void) {
	vector<int> nums;
	getVec(nums);
	int count = 0, n = nums.size();
	// for (int i = 0; i < n; i++) {
	// 	if (nums[i] == 0) swap(nums[i], nums[count++]);
	// }
	// for (int i = count; i < n; i++) {
	// 	if (nums[i] == 1) swap(nums[i], nums[count++]);
	// }
    int p2 = -1, p3 = n, idx = 0;
    while (idx < p3) {
        if (nums[idx] == 0) {
            p2++;
            swap(nums[idx++], nums[p2]);
        } else if (nums[idx] == 2) {
            p3--;
            swap(nums[idx], nums[p3]);
        } else idx++;
    }
    putVec(nums);
}
