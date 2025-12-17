#include "../utils/mystd.hpp"

int main(void) {
	vector<int> nums;
	getVec(nums);
	int n = nums.size();

	// int idx = 0;
	// vector<int> ans(n);
	// for (int i = 0; i < n; i++) {
	//     if (nums[i] != 0) ans[idx++] = nums[i];
	// }
	// while (idx < n) ans[idx++] = 0;
	// for (int i = 0; i < n; i++) nums[i] = ans[i];

	int idx = -1;
	for (int i = 0; i < n; i++)
		if (nums[i] == 0) {
			idx = i;
			break;
		}
	if (idx != -1) {
		for (int i = idx + 1; i < n; i++)
			if (nums[i] != 0) swap(nums[idx++], nums[i]);
	}
	putVec(nums);
}
