#include <vector>
#include <iostream>
using namespace std;

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int j = 0; j < n; j++)
    {
        cin >> vec[j];
    }
    int max = vec[0];
    int min = vec[0];
    for (int i = 1; i < n; i++)
    {
        if (vec[i] > max)
            max = vec[i];
        if (vec[i] < min)
            min = vec[i];
    }
    cout << max << endl;
    cout << min << endl;
    cout << "Result = " << max - min << endl;
    return 0;
}
