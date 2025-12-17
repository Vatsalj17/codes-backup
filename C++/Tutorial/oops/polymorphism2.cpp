#include <iostream>
using namespace std;

class Parent {
public:
    void getInfo() { // Non-virtual
        cout << "Parent::getInfo()" << endl;
    }
    virtual void show() { // Virtual
        cout << "Parent::show()" << endl;
    }
};

class Child : public Parent {
public:
    void getInfo() { // Hides Parent::getInfo()
        cout << "Child::getInfo()" << endl;
    }
    void show() override { // Overrides Parent::show()
        cout << "Child::show()" << endl;
    }
};

int main() {
    Parent* p = new Child(); // Pointer of base type, object of derived type

    cout << "Calling getInfo() (non-virtual): ";
    p->getInfo(); // Always calls Parent's version

    cout << "Calling show() (virtual): ";
    p->show(); // Calls Child's version because of virtual dispatch

    delete p;
}
