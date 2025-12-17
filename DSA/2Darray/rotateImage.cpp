#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n/2; j++) {
            swap(matrix[i][j], matrix[i][n - j - 1]);
        }
    }
}

int main(void) {
    int n;
    cout << "Enter number or rows: ";
    cin >> n;
    vector<vector<int>> arr(n, vector<int>(n));
    cout << "Enter the Vector: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    cout << "Processing the output....\n";
    rotate(arr);
    cout << "The ans: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
