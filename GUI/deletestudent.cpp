#include "deletestudent.h"

DeleteStudent::DeleteStudent(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(800, 700);
    setStyleSheet("QWidget { background-color: #2b2b2b; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(60, 30, 60, 30);
    mainLayout->setSpacing(10);

    // ── Page Title ──────────────────────────────────────
    QLabel *title = new QLabel("Delete Student");
    title->setStyleSheet("QLabel { color: white; font-size: 24px; font-weight: bold; }");
    title->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(title);
    mainLayout->addSpacing(20);

    // ── Student Info Section ─────────────────────────────
    mainLayout->addWidget(createSectionTitle("Student Information"));
    mainLayout->addSpacing(5);

    mainLayout->addWidget(createLabel("Full Name"));
    fullNameInput = createInput("e.g. Nour Khaled");
    mainLayout->addWidget(fullNameInput);

    mainLayout->addWidget(createLabel("Student ID"));
    idInput = createInput("e.g. 2300949");
    mainLayout->addWidget(idInput);

    mainLayout->addStretch();

    // ── Buttons ──────────────────────────────────────────
    QHBoxLayout *btnLayout = new QHBoxLayout();

    cancelBtn = new QPushButton("Cancel");
    cancelBtn->setFixedSize(100, 45);
    cancelBtn->setStyleSheet("QPushButton { background-color: #3498db; color: white; border-radius: 8px; font-size: 14px; }"
                             "QPushButton:hover { background-color: #2980b9; }");

    deleteBtn = new QPushButton("Delete Student");
    deleteBtn->setFixedSize(100, 45);
    deleteBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border-radius: 8px; font-size: 14px; }"
                             "QPushButton:hover { background-color: #c0392b; }");

    btnLayout->addWidget(cancelBtn);
    btnLayout->addSpacing(20);
    btnLayout->addWidget(deleteBtn);
    btnLayout->setAlignment(Qt::AlignHCenter);

    mainLayout->addLayout(btnLayout);

    connect(deleteBtn, &QPushButton::clicked, this, &DeleteStudent::onDeleteClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &DeleteStudent::onCancelClicked);
}

DeleteStudent::~DeleteStudent() {}

void DeleteStudent::onDeleteClicked()
{
    QString fullName = fullNameInput->text();
    QString id       = idInput->text();

    // Check if fields are empty
    if (fullName.isEmpty() || id.isEmpty()) {
        QMessageBox msg;
        msg.setWindowTitle("Missing Info");
        msg.setText("Please fill in all fields before deleting.");
        msg.setIcon(QMessageBox::Warning);
        msg.setStyleSheet(
            "QMessageBox {"
            "  background-color: #2b2b2b;"
            "}"
            "QMessageBox QLabel {"
            "  color: #fdcb6e;"
            "  font-size: 13px;"
            "}"
            "QPushButton {"
            "  background-color: #3498db;"
            "  color: white;"
            "  border-radius: 6px;"
            "  padding: 5px 15px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #2980b9;"
            "}"
            );
        msg.exec();
        return;
    }
    // bool deleted = yourBackend.deleteStudent(fullName, id);
    bool deleted = false; // replace this with your actual backend call

    if (deleted) {
        // Success popup
        QMessageBox::information(this, "Success", "Student \"" + fullName + "\" has been deleted successfully.");
        fullNameInput->clear();
        idInput->clear();
    } else {
        // Student not found popup
        QMessageBox msg;
        msg.setWindowTitle("Not Found");
        msg.setText("No student found with the name \"" + fullName + "\" and ID \"" + id + "\".");
        msg.setIcon(QMessageBox::Warning);
        msg.setStyleSheet(
            "QMessageBox {"
            "  background-color: #2b2b2b;"
            "}"
            "QMessageBox QLabel {"
            "  color: #fdcb6e;"
            "  font-size: 13px;"
            "}"
            "QPushButton {"
            "  background-color: #3498db;"
            "  color: white;"
            "  border-radius: 6px;"
            "  padding: 5px 15px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #2980b9;"
            "}"
            );
        msg.exec();
    }
}


void DeleteStudent::onCancelClicked()
{
    close();
}

// ── Helpers ───────────────────────────────────────────────

QLineEdit* DeleteStudent::createInput(const QString &placeholder)
{
    QLineEdit *input = new QLineEdit();
    input->setPlaceholderText(placeholder);
    input->setFixedHeight(38);
    input->setStyleSheet(
        "QLineEdit {"
        "  background-color: #3c3f41;"
        "  color: white;"
        "  border: 1px solid #555;"
        "  border-radius: 6px;"
        "  padding: 0 10px;"
        "  font-size: 13px;"
        "}"
        "QLineEdit:focus {"
        "  border: 1px solid #3498db;"
        "}"
        );
    return input;
}

QLabel* DeleteStudent::createSectionTitle(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setStyleSheet(
        "QLabel {"
        "  color: #3498db;"
        "  font-size: 15px;"
        "  font-weight: bold;"
        "  border-bottom: 1px solid #3498db;"
        "  padding-bottom: 4px;"
        "}"
        );
    return label;
}

QLabel* DeleteStudent::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setStyleSheet("QLabel { color: #aaaaaa; font-size: 12px; }");
    return label;
}