#include <iostream>
#include <vector>
using namespace std;

// Four ways of printing the vector
void print_vector(vector<int> vec) {
	cout << "Vector: ";
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}
void print_vector2(vector<int> vec) {
	cout << "Vector: ";
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
void print_vector3(vector<int> vec) {
	cout << "Vector: ";
	for (auto it = vec.begin(); it != vec.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
void print_vector4(vector<int> vec) {
	cout << "Vector: ";
	for (auto it : vec) {
		cout << it << " ";
	}
	cout << endl;
}

int main(void) {
	vector<int> v = {1, 3, 5};
	cout << v[0] << " " << v[1] << " " << v[2] << endl;

	v.push_back(1);	 // 1, 3, 5, 1
	print_vector3(v);
	v.emplace_back(2);	// 1, 3, 5, 1, 2
	print_vector4(v);

	// v = {1, 3, 5, 1, 2};
	vector<int>::iterator it = v.begin();
	cout << "v.begin " << endl;
	cout << *it << "\t";  // 1
	it++;
	cout << *it << "\t";  // 3
	it = it + 2;
	cout << *it << "\t";  // 1
	it--;
	cout << *it << "\t";  // 5
	*it--;
	cout << *it << "\t";  // 3
	vector<int>::iterator it2 = v.end();
	cout << "\nv.end ";
	cout << *(it2 - 1) << "\t";	 // 2
	vector<int>::reverse_iterator it3 = v.rend();
	cout << "\nv.rend ";
	cout << *(it3 - 1) << endl;	 // 1
	vector<int>::reverse_iterator it4 = v.rbegin();
	cout << "v.rbegin ";
	cout << *it4 << endl;  // 2

	cout << "v.back " << v.back() << endl;	// 2
	cout << "v.size " << v.size() << endl;	// 5

	v.erase(v.begin());	 // 3, 5, 1, 2
	print_vector(v);
	v.erase(v.begin() + 1, v.begin() + 3);	// 3, 2
	print_vector(v);

	vector<int> v2(5, 12);	// 12, 12, 12, 12, 12
	print_vector2(v2);
	v2.insert(v2.begin() + 2, 56);
	print_vector(v2);  // 12, 12, 56, 12, 12, 12
	v2.erase(v2.end() - 1);
	print_vector2(v2);	// 12, 12, 56, 12, 12
	v2.insert(v2.begin() + 1, 3, 7);
	print_vector3(v2);	// 12, 7, 7, 7, 12, 56, 12, 12

	vector<int> temp(2, 33);
	v2.insert(v2.begin() + 4, temp.begin(),
			  temp.end());	// 12, 7, 7, 7, 33, 33, 12, 56, 12, 12
	print_vector4(v2);

	v2.pop_back();	// 12, 7, 7, 7, 33, 33, 12, 56, 12
	print_vector(v2);

	v.swap(v2);
	cout << "v: ";
	print_vector2(v);
	cout << "v2: ";
	print_vector4(v2);

	v.clear();
	print_vector2(v);

	cout << "Empty: " << v.empty() << "\t" << v2.empty();  // 1   0
}
