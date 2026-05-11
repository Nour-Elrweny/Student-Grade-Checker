#include "addstudent.h"

AddStudent::AddStudent(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(800, 700);
    setStyleSheet("QWidget { background-color: #2b2b2b; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(60, 30, 60, 30);
    mainLayout->setSpacing(10);

    // ── Page Title ──────────────────────────────────────
    QLabel *title = new QLabel("Add Student");
    title->setStyleSheet("QLabel { color: white; font-size: 24px; font-weight: bold; }");
    title->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(title);
    mainLayout->addSpacing(5);

    // ── Student Info Section ─────────────────────────────
    mainLayout->addWidget(createSectionTitle("Student Information"));
    mainLayout->addSpacing(5);

    mainLayout->addWidget(createLabel("Full Name"));
    fullNameInput = createInput("e.g. Nour Khaled");
    mainLayout->addWidget(fullNameInput);

    mainLayout->addWidget(createLabel("Department"));
    deptInput = createInput("e.g. Computer Engineering");
    mainLayout->addWidget(deptInput);

    mainLayout->addWidget(createLabel("Student ID"));
    idInput = createInput("e.g. 2300949");
    mainLayout->addWidget(idInput);

    mainLayout->addSpacing(20);

    // ── Course Info Section ──────────────────────────────
    mainLayout->addWidget(createSectionTitle("Course Information"));
    mainLayout->addSpacing(5);

    mainLayout->addWidget(createLabel("Course Name"));
    courseNameInput = createInput("e.g. Data Structures");
    mainLayout->addWidget(courseNameInput);

    mainLayout->addWidget(createLabel("Course Code"));
    courseCodeInput = createInput("e.g. CSE333s");
    mainLayout->addWidget(courseCodeInput);

    mainLayout->addWidget(createLabel("Grade"));
    gradeInput = createInput("e.g. A");
    mainLayout->addWidget(gradeInput);

    mainLayout->addStretch();

    // ── Buttons ──────────────────────────────────────────
    QHBoxLayout *btnLayout = new QHBoxLayout();

    cancelBtn = new QPushButton("Cancel");
    cancelBtn->setFixedSize(100, 45);
    cancelBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border-radius: 8px; font-size: 14px; }"
                             "QPushButton:hover { background-color: #c0392b; }");

    submitBtn = new QPushButton("Add Student");
    submitBtn->setFixedSize(100, 45);
    submitBtn->setStyleSheet("QPushButton { background-color: #2ecc71; color: white; border-radius: 8px; font-size: 14px; }"
                             "QPushButton:hover { background-color: #27ae60; }");

    btnLayout->addWidget(cancelBtn);
    btnLayout->addSpacing(20);
    btnLayout->addWidget(submitBtn);
    btnLayout->setAlignment(Qt::AlignHCenter);

    mainLayout->addLayout(btnLayout);

    connect(submitBtn, &QPushButton::clicked, this, &AddStudent::onSubmitClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &AddStudent::onCancelClicked);
}

AddStudent::~AddStudent() {}

// ── Helpers ───────────────────────────────────────────────

QLineEdit* AddStudent::createInput(const QString &placeholder)
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

QLabel* AddStudent::createSectionTitle(const QString &text)
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

QLabel* AddStudent::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setStyleSheet("QLabel { color: #aaaaaa; font-size: 12px; }");
    return label;
}

// ── Slots ─────────────────────────────────────────────────

void AddStudent::onSubmitClicked()
{
    // TODO: grab values and save
    QString fullName = fullNameInput->text();
    QString dept     = deptInput->text();
    QString id       = idInput->text();
    QString course   = courseNameInput->text();
    QString code     = courseCodeInput->text();
    QString grade    = gradeInput->text();

    fullNameInput->clear();
    deptInput->clear();
    idInput->clear();
    courseNameInput->clear();
    courseCodeInput->clear();
    gradeInput->clear();

}

void AddStudent::onCancelClicked()
{
    close();
}