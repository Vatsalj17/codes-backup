#include <iostream>
#include <string>
using namespace std;

bool checkEqual(int count1[26], int count2[26]) {
	for (int i = 0; i < 26; i++) {
		if (count1[i] != count2[i]) return false;
	}
	return true;
}

bool checkInclusion(string s1, string s2) {
	int count[26] = {0};
	for (int i = 0; i < s1.size(); i++) {
		int index = s1[i] - 'a';
		count[index]++;
	}
	int i = 0;
	int n = s2.size();
	int windowSize = s1.length();
	if (n < windowSize) return 0;
	int count2[26] = {0};

	// for first window
	while (i < windowSize) {
		int index = s2[i] - 'a';
		count2[index]++;
		i++;
	}
	if (checkEqual(count, count2)) return 1;

    // for rest of windows
	while (i < s2.length()) {
		char newChar = s2[i];
		int index = newChar - 'a';
		count2[index]++;
		char oldChar = s2[i - windowSize];
		index = oldChar - 'a';
		count2[index]--;
		i++;
		if (checkEqual(count, count2)) return 1;
	}
	return 0;
}

int main(void) {
	string s1, s2;
	cout << "Enter s1: ";
	getline(cin, s1);
	cout << "Enter s2: ";
	getline(cin, s2);
	cout << "Ans: " << checkInclusion(s1, s2);
}
