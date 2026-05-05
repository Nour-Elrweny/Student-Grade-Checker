#ifndef NODE_H
#define NODE_H

#include "Student.h"

struct Node {
    Student data;      
    Node* left;        
    Node* right;       

    // Constructor to initialize a node with student data
    Node(Student s) : data(s), left(nullptr), right(nullptr) {}
};

#endif