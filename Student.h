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
    int id;
    vector<Subject> subjects;

public:
    Student(int idNo, string sname, string dep): id(idNo), name(sname), department(dep){}
    int getID(){ return id;}
    string getName(){return name;}
    string getDept(){return department;}
    void setName(string n){ name = n;}
    void setDept(string d){ department = d;}
    void addSub(Subject s){ subjects.push_back(s);}

};
