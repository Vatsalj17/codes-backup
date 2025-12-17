#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sub(string& str, string& temp, vector<string>& ans, int i) {
    if (i >= str.size()) {
        if (temp.size()) ans.push_back(temp);
        return;
    }
    sub(str, temp, ans, i+1);
    temp.push_back(str[i]);
    sub(str, temp, ans, i+1);
    temp.pop_back();
}

vector<string> subsequences(string& str) {
    vector<string> ans;
    string temp;
    sub(str, temp, ans, 0);
    return ans;
}

int main(void) {
    string str;
    cout << "Enter the string: ";
    cin >> str;
    vector<string> ans;
    ans = subsequences(str);
    int n = ans.size();
    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << endl;
}
