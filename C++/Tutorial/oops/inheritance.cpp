#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name;
    int age;
    Person() {
        cout << "Parent constructor\n";
    }
    Person(string n, int a) {
        this->name = n;
        this->age = a;
    }
    ~Person() {
        cout << "Parent destructor\n";
    }
};

class Student: public Person {
public:
    int rollNo;
    Student() {
        cout << "Child constructor\n";
    }
    Student(string n, int a, int r) : Person(n, a) {
        this->rollNo = r;
    }
    void getInfo() {
        cout << "name: " << name << endl;
        cout << "age: " << age << endl;
        cout << "rollNo: " << rollNo << endl;
    }
    ~Student() {
        cout << "Child destructor" << endl;
    }
};

class Teacher {
public:
    string subject;
    double salary;
};

class gradStudent: public Student {
public:
    string research;
    void getInfo2() {
        cout << "Research Topic: " << research << endl;
    }
};

class TA: public Student, public Teacher {

};

int main(void) {
    Student s1;
    s1.name = "Vatsal";
    s1.age = 20;
    s1.rollNo = 8932;
    s1.getInfo();
    gradStudent s2;
    s2.research = "Quantum";
    s2.getInfo2();
    TA t1;
    t1.name = "Tony Stark";
}
