#ifndef STUDENTBST_H
#define STUDENTBST_H
#include "Student.h"
#include "Node.h"



class StudentBST {
private:
    Node* root;

    // Helper functions for recursion
    Node* insertHelper(Node* r, Student s);
    Node* deleteHelper(Node* r, int id);
    Node* findMin(Node* r); // This finds the node with the smallest ID in a subtree
    Student* searchByIdHelper(Node* r, int targetId);
    void filterByMinAvgHelper(Node* r, float minAvg, std::vector<Student>& results);
    void filterByDeptHelper(Node* r, std::string deptName, std::vector<Student>& results);



public:
    StudentBST();
    ~StudentBST();
    void addStudent(Student s);
    void removeStudent(int id);
    Student* searchById(int targetId);
    void filterByMinAverage(float minAvg, std::vector<Student>& results);
    void filterByDept(std::string deptName, std::vector<Student>& results);

    float calculateAverage(const Student& s); // to be implemented later :)


};

#endif
