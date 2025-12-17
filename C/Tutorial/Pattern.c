#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void HackerRank(int n);

int main()
{
    int n;
    printf("Enter a number for the pattern: ");
    scanf("%d", &n);
    // HackerRank(n);
    return 0;
}

void HackerRank(int n)
{
    for (int i = n; i >= 1; i--)
    {
        for (int j = n; j > i; j--)
        {
            printf("%d ", j);
        }
        for (int r = 1; r < 2 * i; r++)
        {
            printf("%d ", i);
        }
        for (int k = i + 1; k <= n; k++)
        {
            printf("%d ", k);
        }
        printf("\n");
    }
    for (int a = 2; a <= n; a++)
    {
        for (int s = n; s > a; s--)
        {
            printf("%d ", s);
        }
        for (int i = 1; i < 2 * a; i++)
        {
            printf("%d ", a);
        }
        for (int d = a + 1; d <= n; d++)
        {
            printf("%d ", d);
        }
        printf("\n");
    }
}