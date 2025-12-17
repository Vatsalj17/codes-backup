#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ans;
    int nRows = matrix.size();
    set<int> s;
    int nCols = matrix[0].size();
    int in = 0;
    int n = nRows * nCols;
    for (int i = 0; i < n; ) {
        for (int j = in; j < nCols - in; j++) {
            ans.push_back(matrix[in][j]);
            i++;
        }
        for (int j = in + 1; j < nRows - in; j++) {
            ans.push_back(matrix[j][nCols - in - 1]);
            i++;
        }
        for (int j = nCols - in - 2; j >= in; j--) {
            ans.push_back(matrix[nRows - in - 1][j]);
            i++;
        }
        for (int j = nRows - in - 2; j >= in + 1; j--) {
            ans.push_back(matrix[j][in]);
            i++;
        }
        in++;
    }
    if (ans.size() >= n) {
        ans.erase(ans.begin() + n, ans.end());
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
    vector<int> ans = spiralOrder(arr);
    cout << "The ans: ";
    for (int i : ans) cout << i << " ";
    cout << endl;
}
