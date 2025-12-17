#include "../utils/mystd.hpp"

bool isPossible(vector<int> &stalls, int k, int mid) {
    int cowCount = 1;
    int lastStall = stalls[0];
    for (int i = 0; i < stalls.size(); i++) {
        if (stalls[i] - lastStall >= mid) {
            cowCount++;
            if (cowCount == k) return true;
            lastStall = stalls[i];
        }
    }
    return false;
}

int aggressiveCows(vector<int> &stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int s = 0;
    int maxi = 0;
    for (int i = 0; i < stalls.size(); i++) {
        maxi = max(maxi, stalls[i]);
    }
    int e = maxi;
    int ans = -1;
    while (s <= e) {
        int mid = (s + e) / 2;
        if (isPossible(stalls, k, mid)) {
            ans = mid;
            s = mid + 1;
        } else {
            e = mid - 1;
        }
    }
    return ans;
}

int main() {
    int n, k;
    cout << "Enter length of arr: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter no of cows: ";
    cin >> k;
    cout << "Enter elements of arr: ";
    for (int i = 0; i < arr.size(); i++) {
        cin >> arr[i]; 
    }
    cout << "Ans: " << aggressiveCows(arr, k) << endl;
    return 0;
}
