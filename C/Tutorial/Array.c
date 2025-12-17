#include <stdio.h>
#include <stdlib.h>

void oddcounter(int array[], int n);
void reverse(int arr[], int n);
void largest(int arr[], int n);
void sec_largest(int arr[], int n);

int main()
{
    int n;
    printf("Enter the length of the array: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    oddcounter(arr, n);
    reverse(arr, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d \n", arr[i]);
    }
    largest(arr, n);
    free(arr);
    return 0;
}

void sec_largest(int arr[], int n)
{
}

void oddcounter(int array[], int n)
{
    int oddf = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] % 2 != 0)
        {
            oddf++;
        }
    }
    printf("Total odd numbers in the array are : %d\n", oddf);
}

void reverse(int arr[], int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        int t = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = t;
    }
}

void largest(int arr[], int n)
{
    int l = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > l)
        {
            l = arr[i];
        }
    }
    printf("Largest amongst all numbers array is %d\n", l);
}
