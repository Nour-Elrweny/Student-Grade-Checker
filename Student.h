#include <iostream>
#include <vector>
using namespace std;


struct Subject {
    string name;
    double grade;
};

class Student{
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

};
