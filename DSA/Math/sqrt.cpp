#include "../utils/mystd.hpp"

int sqrt(int x) {
    long long int beg = 0, end = x;
    long long int ans;
    while (end >= beg) {
        long long int mid = (beg + end) / 2;
        long long int sq = mid * mid;
        if (sq == x)
            return mid;
        else if (sq > x) end = mid - 1;
        else {
            ans = mid;
            beg = mid + 1;
        }
    }
    return ans;
}

double precision(int n, int precision, int temp) {
    double factor = 1;
    double ans = temp;
    for (int i = 0; i < precision; i++) {
        factor = factor / 10;
        for (double j = ans; j * j < n; j = j + factor) {
            ans = j;
        }
    }
    return ans;
}

int main(void) {
    int a;
    cout << "Enter a num: ";
    cin >> a;
    cout << "sqrt of " << a << " is = " << precision(a, 3, sqrt(a)) << endl;
}
