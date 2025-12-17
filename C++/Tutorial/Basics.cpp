#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    int arr[10];
    cout << "Enter an Array\n";
    for (int i = 0; i < 10; i++)
    {
        cin >> arr[i];
    }
    cout << "Entered array\n";
    for (int j = 0; j < 10; j++)
    {
        cout << arr[j] << " ";
    }
    return 0;
}