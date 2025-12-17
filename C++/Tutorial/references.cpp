#include <iostream>
using namespace std;

void print(int& x) {
    cout << x;
}

void print2(int *x) {
    cout << *x;
}

int main(void) {
    int n{4};
    int& ref{n};
    cout << n << endl;
    ref++;
    cout << n << endl;
    print(n);
    print2(&n);
}
