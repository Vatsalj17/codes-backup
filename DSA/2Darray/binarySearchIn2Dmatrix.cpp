#include <iostream>
#include <vector>
using namespace std;

// for matrix sorted line by line, ref. leetcode question no. 74
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    int start = 0;
    int end = n * m - 1;
    while (end >= start) {
        int mid = (start + end) / 2;
        int element = matrix[mid/m][mid%m];
        if (element == target) 
            return true;
        if (element > target) end = mid - 1;
        else start = mid + 1;
    }
    return false;
}

// for matrix with each row and columns in ascending order, ref. leetcode question no. 240
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    int rowIndex = 0;
    int colIndex = m - 1;
    while (rowIndex < n && colIndex >= 0) {
        int element = matrix[rowIndex][colIndex];
        if (element == target) return true;
        else if (element < target) rowIndex++;
        else colIndex--;
    }
    return false;
}

int main(void) {
    int nRows, nCols, target;
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
    cout << "Enter the target: ";
    cin >> target;
    cout << "Processing the output....\n";
    bool ans = searchMatrix(arr, target);
    cout << "Ans: " << ans << endl;
}
