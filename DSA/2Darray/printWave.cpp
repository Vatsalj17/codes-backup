#include <iostream>
#include <vector>
using namespace std;

vector<int> wavePrint(vector<vector<int>> arr, int nRows, int nCols) {
    vector<int> ans;
    for (int j = 0; j < nCols; j++) {
        int i = (j % 2)? nRows - 1 : 0;
        while (i >= 0 && i < nRows) {
            ans.push_back(arr[i][j]);
            if (j % 2) i--;
            else i++;
        }
    }
    return ans;
}

int main(void) {
    int nRows, nCols;
    cout << "Enter number or rows: ";
    cin >> nRows;
    cout << "Enter number or columns: ";
    cin >> nCols;
    vector<vector<int>> arr(nRows, vector<int>(nCols));
    cout << "Enter the Vector: \n";
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            cin >> arr[i][j];
        }
    }
    cout << "Processing the output....\n";
    vector<int> ans = wavePrint(arr, nRows, nCols);
    cout << "The ans: ";
    for (int i : ans) cout << i << " ";
    cout << endl;
}
