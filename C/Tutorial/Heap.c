#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int n) {
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
}

int main (void) {
    int a = 4;
    int *arr = (int*)malloc(1 * sizeof(int));
    int n;
    int ar[5];
    ar[0] = 9;
    ar[1] = 8;
    ar[2] = 7;
    ar[3] = 6;
    int *p = &a;
    *arr = 1;
    *(arr + 1) = 2;
    *(arr + 2) = 3;
    printf("%d\n%p\n%d\n%p\n%p\n%d\n", a, &a, *p, p, p + 1, *p + 1);
    print_arr(arr, 4);
    free(arr);
    *arr = 88;
    printf("\n");
    print_arr(arr, 3);
    printf("\n");
    print_arr(ar, 4);
}
