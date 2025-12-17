#include "../utils/mystd.hpp"

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low, j = high;
    while (i < j) {
        while(arr[i] <= pivot && i < high) i++;
        while(arr[j] > pivot && j > low) j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void qS(vector<int>& arr, int low, int high) {
	if (low < high) {
		int pivot = partition(arr, low, high);
		qS(arr, low, pivot - 1);
		qS(arr, pivot + 1, high);
	}
}

vector<int> quickSort(vector<int>& arr) {
	int low = 0, high = arr.size() - 1;
	qS(arr, low, high);
	return arr;
}

int main(void) {
	vector<int> arr;
	getVec(arr);
	vector<int> ans = quickSort(arr);
	putVec(ans);
}
