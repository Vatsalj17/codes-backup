#include "../utils/mystd.hpp"

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int i = low, j = mid + 1;
    while(i <= mid && j <= high) {
        if (arr[i] >= arr[j]) temp.push_back(arr[j++]);
        else temp.push_back(arr[i++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= high) temp.push_back(arr[j++]);
    int idx = 0;
    for (int i = low; i <= high; i++) arr[i] = temp[idx++];
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int main(void) {
    vector<int> arr;
    getVec(arr);
    mergeSort(arr, 0, arr.size() - 1);
    putVec(arr);
}
