#include <iostream>
using namespace std;

void pattern1(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void pattern2(int n)
{
    int i = 1;
    while (i <= n * n)
    {
        for (int j = 0; j < n; j++)
        {
            cout << i << " ";
            i++;
        }
        cout << endl;
    }
    cout << endl;
}

void pattern3(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j >= 1; j--)
        {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void pattern4(int n)
{
    if (n <= 13)
    {
        for (int i = 1; i <= n; i++)
        {
            char al = 'A' + i - 1;
            for (int j = 1; j <= n; j++)
            {
                cout << al << " ";
                al++;
            }
            cout << endl;
        }
        cout << endl;
    }
}

void pattern5(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            cout << "  ";
        }
        for (int k = 1; k <= i; k++)
        {
            cout << k << " ";
        }
        for (int l = i - 1; l >= 1; l--)
        {
            cout << l << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void pattern6(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int k = 1; k <= n - i + 1; k++)
        {
            cout << k << " ";
        }
        for (int l = 1; l <= 2 * (i - 1); l++)
        {
            cout << "* ";
        }
        for (int j = n - i + 1; j >= 1; j--)
        {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << endl;
    pattern1(n);
    pattern2(n);
    pattern3(n);
    pattern4(n);
    pattern5(n);
    pattern6(n);
    return 0;
}