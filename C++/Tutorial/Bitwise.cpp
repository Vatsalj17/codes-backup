#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "a & b = " << (a & b) << endl;
    cout << "a | b = " << (a | b) << endl;
    cout << "~a = " << ~a << endl;
    cout << "~b = " << ~b << endl;
    cout << "a ^ b = " << (a ^ b) << endl;
    cout << "a << b = " << (a << b) << endl;
    cout << "b << a = " << (b << a) << endl;
    cout << "a >> b = " << (a >> b) << endl;
    cout << "b >> a = " << (b >> a) << endl;
    return 0;
}