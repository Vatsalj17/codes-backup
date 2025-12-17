#include "../utils/mystd.hpp"

// Include Exclude Logic
void subset(vector<int>& nums, vector<vector<int>>& ans, vector<int>& output, int i) {
	if (i >= nums.size()) {
		ans.push_back(output);
		return;
	}

    // exclude
	subset(nums, ans, output, i + 1);

    // include
    int element = nums[i];
	output.push_back(element);
	subset(nums, ans, output, i + 1);
    output.pop_back();
}

vector<vector<int>> subsets(vector<int>& nums) {
	vector<vector<int>> ans;
	vector<int> output;
	subset(nums, ans, output, 0);
	return ans;
}

int main(void) {
	vector<int> vec;
	getVec(vec);
	vector<vector<int>> ans = subsets(vec);
	int n = ans.size();
	cout << "The ans: \n";
	for (int i = 0; i < n; i++) {
        putVec(ans[i]);
		cout << endl;
	}
}
