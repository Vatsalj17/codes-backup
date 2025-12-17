#include <limits.h>
#include <stdio.h>

double Pow(double x, long int n, double a) {
    if (n <= 0) return a;
    if (n & 1) a *= x;
    return Pow(x*x, n >> 1, a);
}

double myPow(double x, int n) {
    long int n2 = n;
    if (n < 0) {
        n2 = -(long)n;
        x = 1 / x;
    }
    return Pow(x, n2, 1);
}

int main(void) {
    double x;
    int n;
    printf("Enter the number: ");
    scanf("%lf", &x);
    // printf("Enter the power: ");
    // scanf("%d", &n);
    n = INT_MIN;
    printf("Ans: %lf", myPow(x, n));
}
