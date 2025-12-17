#include <iostream>
#include <string>
using namespace std;

class Teacher {
private:
    double salary; // data hiding

public:
    // properties / attributes
    string name;
    string dept;
    string subject;

    // non-paramterized constructor
    Teacher() {
        cout << "Hi! I am constructor" << endl;
        dept = "Computer Science";
    }

    // parameterized constructor
    Teacher(string name, string dept, string subject, double salary) {
        this->name = name;
        this->dept = dept;
        this->subject = subject;
        this->salary = salary;
    }
    
    // Copy constructor prototype:
    Teacher(Teacher &origObj) {
        cout << "I am custom copy constructor!\n";
        this->name = origObj.name;
        this->dept = origObj.dept;
        this->subject = origObj.subject;
        this->salary = origObj.salary;
    }
    
    // methods / member functions
    void changeDept(string newDept) {
        dept = newDept;
    }
    // setter
    void setSalary(double s) {
        salary = s;
    }
    // getter
    double getSalary() {
        return salary;
    }
    void getInfo() {
        cout << "Name: "<< name << endl;
        cout << "Department: " << dept << endl;
        cout << "Salary: " << getSalary() << endl;
    }
};

class Student {
public:
    string name;
    int rollNo;
    int age;
};

int main() {
    Teacher t1; // t1 -> object
    Teacher t2("Teach", "CS", "Cpp", 5000);
    t1.name = "Vatsal";
    t1.subject = "OOP";
    t1.setSalary(25000);
    cout << "Details of t1: \n";
    cout << "Name: "<< t1.name << endl;
    cout << "Department: " << t1.dept << endl;
    cout << "Salary: " << t1.getSalary() << endl;

    cout << "\nDetails of t2: \n";
    t2.getInfo();

    cout << "\nDetails of t3: \n";
    Teacher t3(t2); // The invokes the default copy constructor
    t3.getInfo();
    return 0;
}
