#include <stdio.h>

int sumArray(int *arr, int n) {
    if (n == 1) return *arr;
    return *arr + sumArray(arr + 1, n - 1);
}

int main(void) {
    int arr[100];
    int n;
    printf("Enter no. of elements: ");
    scanf("%d", &n);
    printf("Enter the array: ");
    for (int i = 0; i < n; i++) scanf(" %d", &arr[i]);
    printf("Processing ans.....\n");
    int sum = sumArray(arr, n);
    printf("Sum: %d", sum);
}
