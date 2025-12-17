#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int rollNo;
    double *cgpaPtr;

    Student() {
        cgpaPtr = new double;
    }

    /* // Shallow copy
    Student(Student &origObj) {
        this->name = origObj.name;
        this->rollNo = origObj.rollNo;
        this->cgpaPtr = origObj.cgpaPtr;
    } */

    // Deep copy
    Student(Student &origObj) {
        this->name = origObj.name;
        this->rollNo = origObj.rollNo;
        cgpaPtr = new double;
        *cgpaPtr = *(origObj.cgpaPtr);
    }

    void getInfo() {
        cout << "Name: " << name << endl;
        cout << "Roll No.: " << rollNo << endl;
        cout << "cgpa: " << *cgpaPtr << endl;
    }
    
    ~Student() {
        delete cgpaPtr; // we need to free the memory on heap manually
    }
};

int main(void) {
    Student s1;
    s1.name = "Vatsal";
    s1.rollNo = 2;
    *s1.cgpaPtr = 10;
    Student s2(s1);
    *s2.cgpaPtr = 9.2;
    s2.rollNo = 3;
    cout << "Info of s1: " << endl;
    s1.getInfo();
    cout << "Info of s2: " << endl;
    s2.getInfo();
}
