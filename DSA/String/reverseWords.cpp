#include <iostream>
#include <vector>
#include <string>
using namespace std;

string reverseWords(string s) {
    string ans;
    vector<string> tokens;
    for (int i = 0; i < s.size(); i++) {
        string token;
        bool wordFound = false;
        while (s[i] != ' ' && i < s.size()) {
            token.push_back(s[i++]);
            wordFound = true;
        }
        if (wordFound) tokens.push_back(token); 
    }
    for (int i = tokens.size() - 1; i >= 0; i--) {
        ans += tokens[i];
        if (i > 0) ans += " ";
    }
    return ans;
}

int main(void) {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
    string ans = reverseWords(s);
    cout << ans << endl;
}
