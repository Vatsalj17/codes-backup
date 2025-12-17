#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve(string& str, string& temp, vector<string>& ans, int i) {
    if (i >= str.size()) {
        ans.push_back(temp);
        return;
    }
    for (int j = 0; j < str.size(); j++) {
        if (temp.find(str[j]) < str.size()) continue;
        temp.push_back(str[j]);
        solve(str, temp, ans, i + 1);
        temp.pop_back();
    }
}

vector<string> generatePermutations(string &str) {
    sort(str.begin(), str.end());
    vector<string> ans;
    string temp;
    solve(str, temp, ans, 0);
    return ans;
}

int main(void) {
    string str;
    cout << "Enter a string: ";
    cin >> str;
    vector<string> ans = generatePermutations(str);
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
}
