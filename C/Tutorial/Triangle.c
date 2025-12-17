#include <stdio.h>

double factorial(double n)
{
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

double combination(double a, double b)
{
    return (factorial(a) / (factorial(a - b) * factorial(b)));
}

void PascalsTriangle(int n)
{
    for (double i = 0; i < n; i++)
    {
        for (int k = n; k > i; k--)
        {
            printf(" ");
        }
        for (double j = 0; j <= i; j++)
        {
            printf("%ld ", combination(i, j));
        }
        printf("\n");
    }
}

int main(void)
{
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    PascalsTriangle(number);
}