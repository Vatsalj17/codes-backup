#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char getMaxOccuringChar(string& s) {
    //    sort(s.begin(), s.end());
    // int max = 0; 
    //    char ch = s[0];
    // for (int i = 0; i < s.size() - 1; i++) {
    //        int count = 1;
    //        char temp = s[i];
    //        while (s[i] == s[i + 1] && i < s.size() - 1) {
    //            count++;
    //            temp = s[i++];
    //        }
    //        if (count >= max) {
    //            if (count == max && max != 0) {
    //                ch = (ch <= temp)? ch : temp;
    //            } else {
    //                ch = temp;
    //            }
    //            max = count;
    //        }
    // }
    //    return ch;
    int arr[26] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        int n = s[i] - 'a';
        arr[n]++;
    }
    int max = 0, ans = 0;
    for (int i = 0; i < 26; i++) {
        if (arr[i] > max) {
            max = arr[i];
            ans = i;
        }
    }
    return ans + 'a';
}

int main(void) {
	string s;
	cout << "Enter a string: ";
	getline(cin, s);
    char c = getMaxOccuringChar(s);
    cout << "char: " << c << endl;
}
