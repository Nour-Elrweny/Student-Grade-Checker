#include "StudentBST.h"

StudentBST::StudentBST()
{
    root = nullptr;
}

void clearTree(Node* r)
{
    if (r == nullptr)
        return;
    clearTree(r->left);
    clearTree(r->right);
    delete r;
}

StudentBST::~StudentBST()
{
    clearTree(root);
}
// --- ADD FEATURE ---
Node* StudentBST::insertHelper(Node* r, Student s)
{
    if (r == nullptr)
    {
        return new Node(s);
    }
    // Compare using Student ID
    if (s.getId() < r->data.getId())
    {
        r->left = insertHelper(r->left, s);
    }
    else if (s.getId() > r->data.getId())
    {
        r->right = insertHelper(r->right, s);
    }
    return r;
}

void StudentBST::addStudent(Student s) {
    root = insertHelper(root, s);
}

// --- DELETE FEATURE ---
Node* StudentBST::findMin(Node* r)
{
    while (r && r->left != nullptr)
        r = r->left;
    return r;
}

Node* StudentBST::deleteHelper(Node* r, int id)
{
    if (r == nullptr)
        return nullptr;

    if (id < r->data.getId())
    {
        r->left = deleteHelper(r->left, id);
    }
    else if (id > r->data.getId())
    {
        r->right = deleteHelper(r->right, id);
    }
    else
    {

        // Case 1: No child or one child
        if (r->left == nullptr)
        {
            Node* temp = r->right;
            delete r;
            return temp;
        }
        else if (r->right == nullptr)
        {
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

void StudentBST::removeStudent(int id)
{
    root = deleteHelper(root, id);
}

// Search by ID function to be used
Student* StudentBST::searchById(int targetId)
{
    return searchByIdHelper(root, targetId);
}
// Private helper for the original function
Student* StudentBST::searchByIdHelper(Node* r, int targetId)
{
    if (r == nullptr)
        return nullptr;

    if (r->data.getId() == targetId)
    {
        return &(r->data);
    }

    if (targetId < r->data.getId())
    {
        return searchByIdHelper(r->left, targetId);
    }
    else
    {
        return searchByIdHelper(r->right, targetId);
    }
}

// Filter by a min grade function to be used
void StudentBST::filterByMinAverage(float minAvg, std::vector<Student>& results)
{
    filterByMinAvgHelper(root, minAvg, results);
}

// private helper for the filter by a min grade function
void StudentBST::filterByMinAvgHelper(Node* r, float minAvg, std::vector<Student>& results)
{
    if (r == nullptr)
        return;

    if (calculateAverage(r->data) >= minAvg)
    {
        results.push_back(r->data);
    }

    filterByMinAvgHelper(r->left, minAvg, results);
    filterByMinAvgHelper(r->right, minAvg, results);
}

// Filter by dept function to be used
void StudentBST::filterByDept(std::string deptName, std::vector<Student>& results)
{
    filterByDeptHelper(root, deptName, results);
}

// Private helper for the filter by dept function
void StudentBST::filterByDeptHelper(Node* r, std::string deptName, std::vector<Student>& results)
{
    if (r == nullptr)
    {
        return;
    }

    if (r->data.getDept() == deptName)
    {
        results.push_back(r->data);
    }

    filterByDeptHelper(r->left, deptName, results);
    filterByDeptHelper(r->right, deptName, results);
}

float StudentBST::calculateAverage(const Student& s)
{
    // Get the student's subjects
    const vector<Subject>& subs = s.getSubjects();

    // If the student has no subjects, return 0
    if (subs.empty())
        return 0.0f;

    // Sum all grades
    float sum = 0.0f;
    for (int i = 0; i < subs.size(); i++)
    {
        sum += subs[i].grade;
    }

    // Return the average grade
    return sum / subs.size();
}

bool StudentBST::addSubjectToStudent(int id, Subject sub)
{
    // Search for the student by ID
    Student* student = searchById(id);

    // If student is not found, return false
    if (student == nullptr)
        return false;

    // Add the new subject to the student
    student->addSub(sub);
    cout << "added successfully ";
    return true;
}

bool StudentBST::updateSubjectGrade(int id, string subjectName, float newGrade)
{
    // Search for the student by ID
    Student* s = searchById(id);

    // If student is not found, return false
    if (student == nullptr)
        return false; // not found

    // Get the student's subjects so we can update one of them
    vector<Subject>& subs = s->getSubjects();

    // Search for the subject by name
    for (int i = 0; i < subs.size(); i++)
    {
        if (subs[i].name == subjectName)
        {
            // Update the subject grade
            subs[i].grade = newGrade;
            return true;
        }
    }

    // Subject was not found
    return false;
}

void StudentBST::findTopHelper(Node* r, int& topId, float& maxAvg)
{
    // Stop if the current node is empty
    if (r == nullptr)
        return;

    // Calculate the average of the current student
    float currentAvg = calculateAverage(r->data);

    // If this student has a higher average, update topId and maxAvg
    if (currentAvg > maxAvg)
    {
        maxAvg = currentAvg;
        topId = r->data.getId();
    }

    // Continue searching in left and right subtrees
    findTopHelper(r->left, topId, maxAvg);
    findTopHelper(r->right, topId, maxAvg);
}

int StudentBST::getTopStudent()
{
    // If the tree is empty, return -1
    if (root == nullptr)
        return -1;  // no students

    int topId = -1;
    float maxAvg = -1.0f;

    // Start searching from the root
    findTopHelper(root, topId, maxAvg);

    // Return the ID of the top student
    return topId;
}

void StudentBST::findLowestHelper(Node* r, int& lowestId, float& minAvg)
{
    // Stop if the current node is empty
    if (r == nullptr)
        return;

    // Calculate the average of the current student
    float currentAvg = calculateAverage(r->data);

    // If this is the first student or the average is smaller, update lowestId and minAvg
    if (lowestId == -1 || currentAvg < minAvg)
    {
        minAvg = currentAvg;
        lowestId = r->data.getId();
    }

    // Continue searching in left and right subtrees
    findLowestHelper(r->left, lowestId, minAvg);
    findLowestHelper(r->right, lowestId, minAvg);
}

int StudentBST::getLowestStudent()
{
    // If the tree is empty, return -1
    if (root == nullptr)
        return -1;   //  no students 

    int lowestId = -1;
    float minAvg = 0.0f;

    // Start searching from the root
    findLowestHelper(root, lowestId, minAvg);

    // Return the ID of the lowest student
    return lowestId;
}

void StudentBST::getFailedHelper(Node* r, std::vector<Student>& results, float passMark)
{
    // Stop if the current node is empty
    if (r == nullptr)
        return;

    // Calculate the average of the current student
    float avg = calculateAverage(r->data);

    // If the average is less than the pass mark, add the student to results
    if (avg < passMark)
    {
        results.push_back(r->data);
    }

    // Continue searching in left and right subtrees
    getFailedHelper(r->left, results, passMark);
    getFailedHelper(r->right, results, passMark);
}

void StudentBST::getFailedStudents(std::vector<Student>& results, float passMark)
{
    // Clear old results so students do not repeat
    results.clear();

    // Fill the vector with failed students
    getFailedHelper(root, results, passMark);

    // If no failed students were found, print a message
    if (results.empty())
    {
        cout << "No failed students." << endl;
        return;
    }

    // Print the IDs of failed students
    cout << "Failed students IDs: ";
    for (int i = 0; i < results.size(); i++)
    {
        cout << results[i].getId();

        if (i != results.size() - 1)
            cout << ", ";
    }
    cout << endl;
}

void StudentBST::displayStudentReport(int id)
{
    // Search for the student by ID
    Student* studentPtr = searchById(id);

    // If the student is not found, print a message
    if (studentPtr == nullptr)
    {
        cout << "Student not found." << endl;
        return;
    }

    // Create a local object from the found student
    Student student = *studentPtr;

    cout << "----- Student Report -----" << endl;
    cout << "ID: " << student.getId() << endl;
    cout << "Name: " << student.getName() << endl;
    cout << "Department: " << student.getDept() << endl;

    // Get all subjects of this student
    const vector<Subject>& subs = student.getSubjects();

    // If the student has no subjects, print a message
    if (subs.empty())
    {
        cout << "No subjects found." << endl;
    }
    else
    {
        // Print each subject and its grade
        cout << "Subjects and Grades:" << endl;
        for (int i = 0; i < subs.size(); i++)
        {
            cout << subs[i].name << " : " << subs[i].grade << endl;
        }
    }

    // Calculate and print the average
    float avg = calculateAverage(student);
    cout << "Average: " << avg << endl;

    // Print pass/fail status
    if (avg >= 60)
        cout << "Status: Passed" << endl;
    else
        cout << "Status: Failed" << endl;

    cout << "--------------------------" << endl;
}

void StudentBST::displayAllHelper(Node* r)
{
    // Stop if the current node is empty
    if (r == nullptr)
        return;

    // First, go to the left subtree
    displayAllHelper(r->left);

    // Get the current student and calculate the average
    const Student& student = r->data;
    float avg = calculateAverage(student);

    // Print student basic information
    cout << "ID: " << student.getId()
        << " | Name: " << student.getName()
        << " | Department: " << student.getDept()
        << " | Average: " << avg;

    // Print pass/fail status
    if (avg >= 60)
        cout << " | Status: Passed" << endl;
    else
        cout << " | Status: Failed" << endl;

    // Then, go to the right subtree
    displayAllHelper(r->right);
}

void StudentBST::displayAllStudents()
{
    // If the tree is empty, print a message
    if (root == nullptr)
    {
        cout << "No students found." << endl;
        return;
    }

    // Print all students in sorted order by ID
    cout << "----- All Students -----" << endl;
    displayAllHelper(root);
    cout << "------------------------" << endl;
}