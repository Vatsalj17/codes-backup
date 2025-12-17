#include "../utils/mystd.hpp"

vector<int> findArraySum(vector<int> &a, int n, vector<int> &b, int m) {
	int s = (n > m) ? n : m;
	vector<int> ans(s);
	int i = n - 1;
	int j = m - 1;
	int carry = 0;
	int idx = s - 1;
	while (i >= 0 && j >= 0) {
		int sum = a[i] + b[j] + carry;
		ans[idx--] = sum % 10;
		carry = 0;
		if (sum >= 10) {
			carry++;
		}
		i--;
		j--;
	}
	while (i >= 0) {
		ans[idx--] = a[i--] + carry;
		carry = 0;
	}
	while (j >= 0) {
		ans[idx--] = b[j--] + carry;
		carry = 0;
	}
	if (carry == 1) ans.insert(ans.begin(), 1);
	return ans;
}

int main(void) {
	vector<int> a;
	getVec(a);
	vector<int> b;
	getVec(b);
	int n = a.size();
	int m = b.size();
	vector<int> arr = findArraySum(a, n, b, m);
	putVec(arr);
}
