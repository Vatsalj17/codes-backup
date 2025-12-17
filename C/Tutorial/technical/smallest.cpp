#include <stdlib.h>
#include <iostream>
using namespace std;

int main(void) {
    int n;
    cout << "Enter n: ";
    cin >> n;
    int *arr = new int[n];
    cout << "Enter array: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
}
