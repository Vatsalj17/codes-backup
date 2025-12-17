#include <iostream>
#include <string>
using namespace std;

string replaceSpaces(string& str) {
    string ans;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            ans.append("@40");
        } else {
            ans.push_back(str[i]);
        }
    }
    return ans;
}

int main(void) {
    string str;
    getline(cin, str);
    string ans = replaceSpaces(str);
    cout << ans << endl;
}
