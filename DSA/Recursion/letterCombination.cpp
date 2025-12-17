#include <iostream>
#include <vector>
#include <string>
using namespace std;

void solve(string& digits, string& temp, vector<string>& ans, int i, vector<string>& alpha) {
    if (i >= digits.size()) {
        ans.push_back(temp);
        return;
    }
    int num = digits[i] - '0';
    string val = alpha[num - 2];
    for (int j = 0; j < val.size(); j++) {
        temp.push_back(val[j]);
        solve(digits, temp, ans, i + 1, alpha);
        temp.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> alpha = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ans;
    string temp;
    solve(digits, temp, ans, 0, alpha);
    return ans;
}

int main(void) {
    string num;
    cout << "Enter a number: ";
    cin >> num;
    vector<string> ans = letterCombinations(num);
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
}
