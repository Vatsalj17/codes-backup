#include "../utils/mystd.hpp"

void solve(vector<int>& nums, vector<vector<int>>& ans, int i) {
	if (i >= nums.size()) {
		ans.push_back(nums);
		return;
	}
	for (int j = i; j < nums.size(); j++) {
        swap(nums[i], nums[j]);
        solve(nums, ans, i + 1);
        swap(nums[i], nums[j]);
	}
}

vector<vector<int>> permute(vector<int>& nums) {
	vector<vector<int>> ans;
	vector<int> temp;
	solve(nums, ans, 0);
	return ans;
}

int main(void) {
	vector<int> vec;
	getVec(vec);
	vector<vector<int>> ans = permute(vec);
	int n = ans.size();
	int m = ans[0].size();
	cout << "Ans: \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
}
