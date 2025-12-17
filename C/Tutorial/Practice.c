#include <stdio.h>
#include <string.h>

#define MAX 200

void product(char *str, int a)
{
    int n = strlen(str);
    int r = str[n - 1] - '0';
    int p = a * r;
    int k = 0;
    while (p > 0)
    {
        str[n - 1] = ((str[n - 1] * (p % 10)) + k) + '0';
        p /= 10;
        n--;
    }
}

int main(void)
{
    int t;
    printf("Enter number of inputs: ");
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        int n;
        printf("Enter a number: ");
        scanf("%d", &n);
        char ans[MAX];
        ans[0] = '1';
        ans[1] = '\0';
        for (int j = 1; j <= n; j++)
        {
            product(ans, j);
        }
        for (int k = 0; ans[k] != '\0'; k++)
        {
            printf("%c", ans[k]);
        }
        printf("\n%ld", strlen(ans));
    }
}
