#include <iostream>
using namespace std;

// abstract class
class Shape {
    virtual void draw() = 0; // pure virtual function
};

class Circle: public Shape {
public:
    void draw() {
        cout << "Drawing a circle\n";
    }
};

int main(void) {
    Circle c1;
    c1.draw();
}
