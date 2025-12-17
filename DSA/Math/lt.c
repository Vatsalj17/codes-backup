#include <stdlib.h>
#include <string.h>
int* decimalRepresentation(int n, int* returnSize) {
    int *ans = malloc(sizeof(int));
    int i = 1;
    int p = 1;
    while (n) {
        int r = n % 10;
        if (r) {
            i++;
            ans = realloc(ans, i * sizeof(int));
            memmove(ans + 1, ans, (i - 1) * sizeof(int));
            ans[0] = r * p;
        }
        p *= 10;
        n /= 10;
    }
    *returnSize = i - 1;
    return ans;
}
