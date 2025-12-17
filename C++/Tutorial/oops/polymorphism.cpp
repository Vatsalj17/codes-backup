#include <iostream>
#include <string>
using namespace std;

// Function overloading
class Print {
public:
    void show(int x) {
        cout << "int: " << x << endl;
    }
    void show(char x) {
        cout << "char: " << x << endl;
    }
    void show(string x) {
        cout << "string: " << x << endl;
    }
};

// Function overriding
class Parent {
public:
    void getInfo() {
        cout << "Parent Class\n";
    }
    virtual void show() {
        cout << "Hello from virtaul func in parent\n";
    }
};
class Child: public Parent {
public:
    void getInfo() {
        cout << "Child Class\n";
    }
    void show() override {
        cout << "Hello from child\n";
    }
};

int main(void) {
    Print p1;
    p1.show(1);
    p1.show('a');
    p1.show("Hi!");
    Parent p;
    p.getInfo();
    p.show();
    Child c;
    c.getInfo();
    c.show();
}
