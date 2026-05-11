#ifndef STUDENT_H
#define STUDENT_H
using namespace std;

#include <iostream>
#include <vector>
#include <string>

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
    // Single constructor
    Student(int sid, std::string sname, std::string dep)
        : id(sid), name(sname), department(dep) {}

    // Getters
    int getId() const               { return id; }
    string getName() const     { return name; }
    string getDept() const     { return department; }
    const vector<Subject>& getSubjects() const { return subjects; }

    // Setters
    void setName(string n)     { name = n; }
    void setDept(string d)     { department = d; }
    void setId(int i)               { id = i; }
    void addSub(Subject s)          { subjects.push_back(s); }
};

#endif