#include <bits/stdc++.h>
using namespace std;

int main() {
	int num, i, temp;
	cin >> num;
	vector<int> a;
	vector<int> b;
	for (i = 0; i < num; i++) {
		cin >> temp;
        a.push_back(temp);
	}
	for (i = 0; i < num; i++) {
		cin >> temp;
        b.push_back(temp);
	}
	int min = a[0], count = 0;
	for (i = 1; i < num; i++) {
		if (a[i] <= min)
			min = a[i];
	}
	for (i = 0; i < num; i++) {
		if (a[i] != min) {
			while (a[i] >= min) {
				a[i] -= b[i];
				count++;
			}
			if (a[i] != min) {
				count = -1;
				break;
			}
		}
	}
	cout << count;
	return 0;
}