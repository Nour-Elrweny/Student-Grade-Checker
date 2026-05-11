#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

class AddStudent : public QWidget
{
    Q_OBJECT

public:
    AddStudent(QWidget *parent = nullptr);
    ~AddStudent();

private slots:
    void onSubmitClicked();
    void onCancelClicked();

private:
    // Student Info fields
    QLineEdit *fullNameInput;
    QLineEdit *deptInput;
    QLineEdit *idInput;

    // Course Info fields
    QLineEdit *courseNameInput;
    QLineEdit *courseCodeInput;
    QLineEdit *gradeInput;

    // Buttons
    QPushButton *submitBtn;
    QPushButton *cancelBtn;

    // Helper to create styled input fields
    QLineEdit* createInput(const QString &placeholder);
    // Helper to create section labels
    QLabel* createSectionTitle(const QString &text);
    // Helper to create field labels
    QLabel* createLabel(const QString &text);
};

#endif