#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, sum = 0, max, temp;
    printf("Enter value of n: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    int *arr2 = (int *)malloc(n * sizeof(int));
    printf("Enter elements of array= ");
    for (int z = 0; z < n; z++)
    {
        scanf("%d", &arr[z]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < n - i + 1; j++)
        {
            sum = 0;
            for (int k = j; k < j + i; k++)
            {
                sum += arr[k];
            }
            if ((j == 0 && i == 1) || sum > max)
            {
                max = sum;
                temp = i;
                for (int k = j, l = 0; k < j + i; k++, l++)
                {
                    arr2[l] = arr[k];
                }
            }
        }
    }
    printf("Largest sum is %d\n", max);
    printf("Subarray with largest sum is ");
    for (int m = 0; m < temp; m++)
    {
        printf("%d ", arr2[m]);
    }
    free(arr);
    free(arr2);
}