#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int r1, c1, r2, c2, i, j;
    printf("Enter the no. of rows and columns of first matrix: ");
    scanf("%d%d", &r1, &c1);
    printf("Enter the no. of rows and columns of second matrix: ");
    scanf("%d%d", &r2, &c2);
    if (c1 != r2)
    {
        printf("Multiplication not possible");
        return 0;
    }
    int **arr1 = (int **)malloc(r1 * sizeof(int *));
    for (i = 0; i < r1; i++)
    {
        arr1[i] = (int *)malloc(c1 * sizeof(int));
    }
    int **arr2 = (int **)malloc(r2 * sizeof(int *));
    for (i = 0; i < r2; i++)
    {
        arr2[i] = (int *)malloc(c2 * sizeof(int));
    }
    printf("Enter the first matrix: \n");
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            scanf("%d", &arr1[i][j]);
        }
    }
    printf("Enter the second matrix: \n");
    for (i = 0; i < r2; i++)
    {
        for (j = 0; j < c2; j++)
        {
            scanf("%d", &arr2[i][j]);
        }
    }
    int **product = (int **)calloc(r1, sizeof(int *));
    for (i = 0; i < r1; i++)
    {
        product[i] = (int *)calloc(c2, sizeof(int));
    }
    printf("Product of both matrix: \n");
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            for (int k = 0; k < c1; k++)
            {
                product[i][j] += arr1[i][k] * arr2[k][j];
            }
            printf("%d ", product[i][j]);
        }
        printf("\n");
    }
    for (i = 0; i < r1; i++)
    {
        free(arr1[i]);
        free(product[i]);
    }
    for (i = 0; i < r2; i++)
    {
        free(arr2[i]);
    }
    free(arr1);
    free(arr2);
    free(product);
}