#include "mystd.hpp"

void getVec(vector<int>& arr) {
    int n;
    cout << "Enter length of array: ";
    cin >> n;
    arr.resize(n);
    cout << "Enter array: ";
    for (int i = 0; i < arr.size(); i++) cin >> arr[i];
}

void putVec(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) 
        cout << arr[i] << " ";
    cout << endl;
}
