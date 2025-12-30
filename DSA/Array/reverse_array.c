#include "../utils/mystd.h"

int main(void) {
    int* arr, s;
    getArr(&arr, &s);
    int n = s - 1;
    int m;
    printf("Enter Index: ");
    scanf("%d", &m);
    int mid = (n + m) / 2;
    int idx = 0;
    for (int i = m + 1; i <= mid; i++) {
        swap(&arr[i], &arr[n - idx]);
        idx++;
    }
    putArr(arr, s);
}
