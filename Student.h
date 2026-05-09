#ifndef STUDENT_H
#define STUDENT_H

using namespace std;
#include <iostream>
#include <vector>
#include <string>

// The Student class represents a student with their name, department, ID, and a list of subjects with their corresponding grades.
struct Subject {
    std::string name;
    double grade;
};

class Student {
private:
    int id;
    string name;
    string department;
    vector<Subject> subjects;
    

public:
    Student( int sid,string sname, string dep): id(sid) , name(sname), department(dep){}
    string getName(){return name;}
    string getDept(){return department;}
    int getId() const { return id; }
    void setName(string n){ name = n;}
    void setDept(string d){ department = d;}
    void setId(int i){ id = i;}
    void addSub(Subject s){ subjects.push_back(s);}

    Student(int idNo, std::string dep, std::string sname) : name(sname), department(dep), id(idNo) {}

    int getId() { return id; }

    //Getters
    string getName() { return name; }
    string getDept() { return department; }

    //Setters
    void setName(string n) { name = n; }
    void setDept(string d) { department = d; }
    void addSub(Subject s) { subjects.push_back(s); }
};

#endif
