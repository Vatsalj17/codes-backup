#include "../utils/mystd.hpp"

bool isPossible(vector<int> &arr, int n, int m, int mid) {
    int studentCount = 1;
    int pageSum = 0;
    for (int i = 0; i < n; i++) {
        if (pageSum + arr[i] <= mid) {
            pageSum += arr[i];
        } else {
            studentCount++;
            if (studentCount > m || arr[i] > mid) return false;
            pageSum = arr[i];
        }
    }
    return true;
}

int findPages(vector<int> &arr, int n, int m) {
    int beg = 0, end = 0;
    for (int i = 0; i < arr.size(); i++) {
        end += arr[i];
    }
    int ans = -1;
    while(beg <= end) {
        int mid = (beg + end) / 2;
        if (isPossible(arr, n, m, mid)) {
            ans = mid;
            end = mid - 1;
        } else {
            beg = mid + 1;
        }
    }
    return ans;
}

int main() {
    int n, m;
    cout << "Enter no. of books: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter no. of students: ";
    cin >> m;
    cout << "Enter no. of pages in each book: ";
    for (int i = 0; i < arr.size(); i++) {
        cin >> arr[i]; 
    }
    cout << "Max pages = " << findPages(arr, n, m) << endl;
    return 0;
}
