#include "../utils/mystd.hpp"

int main(void) {
    vector<int> nums1;
    vector<int> nums2;
    getVec(nums1);
    getVec(nums2);
    int n = nums1.size();
    int m = nums2.size();
    vector<int> ans(n + m);
    nums1.insert(nums1.end(), m, 0);
    int i = 0, j = 0, idx = 0;
    while (i < n && j < m) {
        if (nums1[i] >= nums2[j]) {
            ans[idx++] = nums2[j++];
        } else {
            ans[idx++] = nums1[i++];
        }
    }
    while (idx < n + m) {
        if (i < n) {
            ans[idx++] = nums1[i++];
        } else if (j < m) {
            ans[idx++] = nums2[j++];
        }
    }
    putVec(ans);
}
