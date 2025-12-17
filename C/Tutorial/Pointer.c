#include <stdio.h>

void Tentimes(int *n);
void sna(int m, int n, int *sum, int *avg);

void pointer_declearation() {
    int n = 5;
    int *p1 = &n;
    int* p2 = &n;
    int * p3 = &n;
    int*p4 = &n;
    // these all are the same
}

int main()
{
    int m, n, sum, avg;
    printf("Enter 2 numbers: ");
    scanf("%d %d", &m, &n);
    int *lol;
    lol = &m;
    int **xd;
    xd = &lol;
    printf("%d\n", **xd);
    // Tentimes(lol);
    sna(m, n, &sum, &avg);
    printf("Sum: %d & Avg: %d\n", sum, avg);
    // printf("%d\n", m);
    // printf("%u\n", lol);
    printf("%u\n", &m);
    // printf("%d\n", *lol);
    // printf("%d\n", xd);
    return 0;
}

void Tentimes(int *n)
{
    *n = 10 * (*n);
    printf("10x of the number is: %d\n", *n);
}

void sna(int m, int n, int *sum, int *avg)
{
    *sum = m + n;
    *avg = (n + m) / 2;
}
