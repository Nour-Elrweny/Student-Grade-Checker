#ifndef NODE_H
#define NODE_H

#include "Student.h"

// The Node struct represents a node in a binary search tree, containing student data and pointers to left and right child nodes.
struct Node {
    Student data;      
    Node* left;        
    Node* right;       

    // Constructor to initialize a node with student data
    Node(Student s) : data(s), left(nullptr), right(nullptr) {}
};

#endif