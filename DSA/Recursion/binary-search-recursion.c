#include <stdio.h>

int binarySearch(int *arr, int s, int e, int k) {
    if (s > e) return -1;
    int mid = (s + e) / 2;
    if (arr[mid] == k) return mid;
    else if (arr[mid] < k) return binarySearch(arr, mid + 1, e, k);
    else return binarySearch(arr, s, mid - 1, k);
}

int main(void) {
    int arr[100];
    int n, k;
    printf("Enter no. of elements: ");
    scanf("%d", &n);
    printf("Enter the array: ");
    for (int i = 0; i < n; i++) scanf(" %d", &arr[i]);
    printf("Enter the element to search for: ");
    scanf("%d", &k);
    printf("Processing ans.....\n");
    int s = 0, e = n - 1;
    int ans = binarySearch(arr, s, e, k);
    if (ans != -1) printf("Found at %d\n", ans);
    else printf("Not Found\n");
}
