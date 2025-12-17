#include "../utils/mystd.hpp"

int rsearch(vector<int>& nums, int target) {
    int n = nums.size();
	int beg = 0, end = n - 1;
	while (end > beg) {
		int mid = (beg + end) / 2;
		if (nums[mid] >= nums[end])
			beg = mid + 1;
		else
			end = mid;
	}
	int pivot = end;
	if (target >= nums[pivot] && target <= nums[n - 1]) {
		beg = pivot;
		end = n - 1;
	} else {
		beg = 0;
		end = pivot - 1;
	}
	while (end >= beg) {
		int mid = (beg + end) / 2;
		if (nums[mid] == target)
			return mid;
		else if (nums[mid] > target)
			end = mid - 1;
		else
			beg = mid + 1;
	}
	return -1;
}

int binary_search(vector<int>& arr, int n, int k) {
	int beg = 0, end = n - 1;
	while (end >= beg) {
		int mid = (beg + end) / 2;
		if (arr[mid] == k)
			return mid;
		else if (arr[mid] > k)
			end = mid - 1;
		else
			beg = mid + 1;
	}
	return -1;
}

int main(void) {
	int k;
	vector<int> arr;
	getVec(arr);
	cout << "Enter searching element: ";
	cin >> k;
	int idx = rsearch(arr, k);
	cout << "Found at " << idx << endl;
}
