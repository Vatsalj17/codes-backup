#include "../utils/mystd.hpp"

int main(void) {
    vector<int> arr;
    getVec(arr);
    int n = arr.size() - 1;
    int m;
    cout << "Enter Index: ";
    cin >> m;
    int mid = (n + m) / 2;
    int idx = 0;
    for (int i = m + 1; i <= mid; i++) {
        swap(arr[i], arr[n - idx]);
        idx++;
    }
    putVec(arr);
}
