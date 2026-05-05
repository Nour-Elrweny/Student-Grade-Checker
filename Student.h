#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>

struct Subject {
    std::string name;
    double grade;
};

class Student {
private:
    std::string name;
    std::string department;
    int id;
    std::vector<Subject> subjects;

public:

    Student(int idNo, std::string dep, std::string sname) : name(sname), department(dep), id(idNo) {}

    int getId() { return id; }

    std::string getName() { return name; }
    std::string getDept() { return department; }

    void setName(std::string n) { name = n; }
    void setDept(std::string d) { department = d; }
    void addSub(Subject s) { subjects.push_back(s); }
};

#endif
