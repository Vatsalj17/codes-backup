#include "../utils/mystd.h"
#include <string.h>

int* findArraySum(int* a, int n, int* b, int m, int* returnSize) {
    if (!a || !b || n <= 0 || m <= 0 || !returnSize)
        return NULL;
	int s = (n > m) ? n : m;
	int* ans = calloc(s, sizeof(int));
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
        int result = a[i--] + carry;
		ans[idx--] = result % 10;
		carry = result / 10;
	}
	while (j >= 0) {
        int result = b[j--] + carry;
		ans[idx--] = result % 10;
		carry = result / 10;
	}
	if (carry > 0) {
        ans = realloc(ans, (1 + s) * sizeof(int));
        memmove(ans + 1, ans, s * sizeof(int));
        ans[0] = 1;
        s++;
    }
    *returnSize = s;
	return ans;
}

int main(void) {
	int* a;
	int* b;
	int n;
	int m;
	getArr(&a, &n);
	getArr(&b, &m);
    int k;
	int* arr = findArraySum(a, n, b, m, &k);
	putArr(arr, k);
    free(a);
    free(b);
    free(arr);
}
