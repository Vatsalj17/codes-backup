#include <iostream>
using namespace std;

int day{1};
string week{7};

int main(void) {
    switch (day) {
        case 1: 
        cout << "Shorya\n";
        [[fallthrough]];
        case 2:
        cout << "Second\n";
        [[fallthrough]];
        case 3:
        cout << "without fallthrough\n";
        default:
        cout << "from default\n";
    }
    cout << week << endl;
}
