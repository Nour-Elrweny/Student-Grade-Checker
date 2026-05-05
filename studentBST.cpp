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
    }
    else if (s.getId() > r->data.getId()) {
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

// Search by ID function to be used
Student* StudentBST::searchById(int targetId) {
    return searchByIdHelper(root, targetId);
}
// Private helper for the original function
Student* StudentBST::searchByIdHelper(Node* r, int targetId) {
    if (r == nullptr) return nullptr;

    if (r->data.getId() == targetId) {
        return &(r->data);
    }

    if (targetId < r->data.getId()) {
        return searchByIdHelper(r->left, targetId);
    } else {
        return searchByIdHelper(r->right, targetId);
    }
}

// Filter by a min grade function to be used
void StudentBST::filterByMinAverage(float minAvg, std::vector<Student>& results) {
    filterByMinAvgHelper(root, minAvg, results);
}

// private helper for the filter by a min grade function
void StudentBST::filterByMinAvgHelper(Node* r, float minAvg, std::vector<Student>& results) {
    if (r == nullptr) return;

    if (calculateAverage(r->data) >= minAvg) {
        results.push_back(r->data);
    }

    filterByMinAvgHelper(r->left, minAvg, results);
    filterByMinAvgHelper(r->right, minAvg, results);
}

// Filter by dept function to be used
void StudentBST::filterByDept(std::string deptName, std::vector<Student>& results) {
    filterByDeptHelper(root, deptName, results);
}

// Private helper for the filter by dept function
void StudentBST::filterByDeptHelper(Node* r, std::string deptName, std::vector<Student>& results) {
    if (r == nullptr) {
        return;
    }

    if (r->data.getDept() == deptName) {
        results.push_back(r->data);
    }

    filterByDeptHelper(r->left, deptName, results);
    filterByDeptHelper(r->right, deptName, results);
}

float StudentBST::calculateAverage(const Student& s) {
    // Your logic

}
