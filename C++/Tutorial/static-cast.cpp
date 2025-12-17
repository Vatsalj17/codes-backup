#include <iostream>
using namespace std;

int main(void) {
    int n = 4;
    float m = static_cast<float>(n);
    m += 0.1;
    cout << n << ", " << m << endl;
}
