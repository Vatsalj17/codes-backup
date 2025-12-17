#include <iostream>
using namespace std;

void pattern(int n) {
    char ch = 'a';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            cout << " ";
        }
        for (int j = 0; j < i + 1; j++) {
            cout << ch++ << " ";
        }
        cout << endl;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            cout << " ";
        }
        for (int j = 0; j < n - i; j++) {
            cout << ch++ << " ";
        }
        cout << endl;
    }
}

int main(void) {
    int n;
    cout << "Enter n: ";
    cin >> n;
    pattern(n);
}
