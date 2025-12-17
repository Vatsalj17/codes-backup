#include <climits>
#include "../utils/mystd.hpp"

int maxSub(vector<int>& nums) {
	int sum = 0;
	int maxSum = INT_MIN;
	for (int i : nums) {
		sum += i;
		maxSum = max(sum, maxSum);
		if (sum < 0) sum = 0;
	}
	return maxSum;
}

int main(void) {
	vector<int> ajay;
	getVec(ajay);
	int ans = maxSub(ajay);
	cout << "Ans. " << ans << endl;
}
