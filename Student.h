#include <iostream>
#include <vector>
using namespace std;


struct Subject {
    string name;
    double grade;
};

class Student{
private:
    string name;
    string department;
    vector<Subject> subjects;

public:
    Student(string sname, string dep): name(sname), department(dep){}
    string getName(){return name;}
    string getDept(){return department;}
    void setName(string n){ name = n;}
    void setDept(string d){ department = d;}
    void addSub(Subject s){ subjects.push_back(s);}

};
