#ifndef STUDENTBST_H
#define STUDENTBST_H

#include "Node.h"

class StudentBST {
private:
    Node* root;

    // Helper functions for recursion
    Node* insertHelper(Node* r, Student s);
    Node* deleteHelper(Node* r, int id);
    Node* findMin(Node* r); // This finds the node with the smallest ID in a subtree
    

public:
    StudentBST();
    ~StudentBST();
    void addStudent(Student s);
    void removeStudent(int id);
    
};

#endif