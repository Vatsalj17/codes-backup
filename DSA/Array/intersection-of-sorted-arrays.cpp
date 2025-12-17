#include "../utils/mystd.hpp"

vector<int> intersection(vector<int>& a, vector<int>& b) {
	vector<int> ans;
	int n = a.size(), m = b.size();
	int i = 0, j = 0;
	while (i < n && j < m) {
		if (a[i] == b[j]) {
			if (ans.size() == 0 || ans.back() != b[j]) ans.emplace_back(b[j]);
			j++;
		} else if (a[i] > b[j])
			j++;
		else
			i++;
	}
	return ans;
}

int main(void) {
	vector<int> arr1, arr2;
	getVec(arr1);
	getVec(arr2);
	putVec(intersection(arr1, arr2));
}
