#include "../mystd.h"
#include <cctype>

bool check(string s) {
    string ans;
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) ans.push_back(s[i]);
        else if (isalpha(s[i])) ans.push_back(tolower(s[i]));
    }
    int beg = 0, end = ans.size() - 1;
    while (end > beg) {
        if (ans[beg++] != ans[end--]) return false;
    }
    return true;
}

int main(void) {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
    // cout << "This is the string: " << s << endl;
    bool val = check(s);
    cout << "Ans: " << val << endl;
}
