#include "StudentBST.h"

StudentBST::StudentBST() {
    root = nullptr;
}

void clearTree(Node* r) {
    if (r == nullptr) return;
    clearTree(r->left);
    clearTree(r->right);
    delete r;
}


StudentBST::~StudentBST() {
    clearTree(root);
}
// --- ADD FEATURE ---
Node* StudentBST::insertHelper(Node* r, Student s) {
    if (r == nullptr) {
        return new Node(s);
    }
    // Compare using Student ID
    if (s.getId() < r->data.getId()) {
        r->left = insertHelper(r->left, s);
    } else if (s.getId() > r->data.getId()) {
        r->right = insertHelper(r->right, s);
    }
    return r;
}

void StudentBST::addStudent(Student s) {
    root = insertHelper(root, s);
}

// --- DELETE FEATURE ---
Node* StudentBST::findMin(Node* r) {
    while (r && r->left != nullptr) r = r->left;
    return r;
}

Node* StudentBST::deleteHelper(Node* r, int id) {
    if (r == nullptr) return nullptr;

    if (id < r->data.getId()) {
        r->left = deleteHelper(r->left, id);
    } else if (id > r->data.getId()) {
        r->right = deleteHelper(r->right, id);
    } else {
        
        // Case 1: No child or one child
        if (r->left == nullptr) {
            Node* temp = r->right;
            delete r;
            return temp;
        } else if (r->right == nullptr) {
            Node* temp = r->left;
            delete r;
            return temp;
        }
        // Case 2: Two children
        // Get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(r->right);
        r->data = temp->data;
        r->right = deleteHelper(r->right, temp->data.getId());
    }
    return r;
}

void StudentBST::removeStudent(int id) {
    root = deleteHelper(root, id);
}
