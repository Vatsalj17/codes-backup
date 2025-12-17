#include <iostream>
#include <string>
using namespace std;

// string removeOccurance(string& s, string& part) {
// 	string ans;
// 	int n = s.size();
// 	int p = part.size();
// 	bool check = true;
// 	while (check) {
//         check = false;
// 		for (int i = 0; i < n; i++) {
// 			int idx = 0;
// 			string temp;
// 			while (s[i] == part[idx] && i < n) {
// 				if (idx >= p) {
// 					break;
// 				}
// 				temp.push_back(part[idx++]);
// 				i++;
// 			}
// 			if (temp != part) {
// 				ans.append(temp);
// 			} else {
//                 check = true;
//             }
// 			ans.push_back(s[i]);
//             if (idx) i--;
// 		}
//         cout << "after for ans: " << ans << endl;
//         s = ans;
//         n = s.size();
// 	}
// 	return ans.substr(0, n/2);
// }

string removeOccurance(string& s, string& part) {
    while (s.length() != 0 && s.find(part) != string::npos) {
        s.erase(s.find(part), part.length());
    }
    return s;
}

int main(void) {
	string s, part;
	cout << "Enter a string: ";
	getline(cin, s);
	cout << "Enter the patter: ";
	getline(cin, part);
	string ans = removeOccurance(s, part);
	cout << "The ans is: " << ans << endl;
}
