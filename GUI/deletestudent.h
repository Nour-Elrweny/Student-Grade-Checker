#ifndef DELETESTUDENT_H
#define DELETESTUDENT_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

class DeleteStudent : public QWidget
{
    Q_OBJECT

public:
    DeleteStudent(QWidget *parent = nullptr);
    ~DeleteStudent();

private slots:
    void onDeleteClicked();
    void onCancelClicked();

private:
    QLineEdit *fullNameInput;
    QLineEdit *idInput;

    QPushButton *deleteBtn;
    QPushButton *cancelBtn;

    QLineEdit* createInput(const QString &placeholder);
    QLabel* createSectionTitle(const QString &text);
    QLabel* createLabel(const QString &text);
};

#endif // DELETESTUDENT_H