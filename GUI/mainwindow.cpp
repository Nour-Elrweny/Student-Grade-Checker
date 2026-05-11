#include "mainwindow.h"
#include "addstudent.h"
#include "deletestudent.h"
#include "reportsummaries.h"
#include "search.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window title
    setWindowTitle("Student Grade Checker");

    // Create central widget and vertical layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Set window size (width, height)
    setFixedSize(800, 700);

    // Set background colour
    setStyleSheet("QMainWindow { background-color: #2b2b2b; }");

    // Create title label
    QLabel *title = new QLabel("Student Grade Checker");

    // Style the title
    title->setStyleSheet("QLabel { color: white; font-size: 24px; font-weight: bold; }");


    // Create 3 buttons
    Add = new QPushButton("Add Student", this);
    Delete = new QPushButton("Delete Student", this);
    SearchandFilter = new QPushButton("Search and Filter", this);
    Summaries = new QPushButton("Summaries", this);


    // Set button sizes (width, height)
    Add->setFixedSize(200, 50);
    Delete->setFixedSize(200, 50);
    SearchandFilter->setFixedSize(200, 50);
    Summaries->setFixedSize(200, 50);

    // Set button colours using StyleSheet
    Add->setStyleSheet("QPushButton { background-color: #ff6b6b; color: white; border-radius: 8px; }"
                           "QPushButton:hover { background-color: #c0392b; }");

    Delete->setStyleSheet("QPushButton { background-color: #f1c40f; color: white; border-radius: 8px; }"
                       "QPushButton:hover { background-color: #f39c12; }");

    SearchandFilter->setStyleSheet("QPushButton { background-color: #2ecc71; color: white; border-radius: 8px; }"
                           "QPushButton:hover { background-color: #27ae60; }");

    Summaries->setStyleSheet("QPushButton { background-color: #3498db; color: white; border-radius: 8px; }"
                           "QPushButton:hover { background-color: #2980b9; }");



    layout->addStretch();

    // Add buttons to layout
    layout->addWidget(title, 0, Qt::AlignHCenter);   // title first
    layout->addWidget(Add, 0, Qt::AlignHCenter);
    layout->addWidget(Delete, 0, Qt::AlignHCenter);
    layout->addWidget(SearchandFilter, 0, Qt::AlignHCenter);
    layout->addWidget(Summaries, 0, Qt::AlignHCenter);

    layout->addStretch();

    // Set the central widget
    setCentralWidget(centralWidget);

    // Connect buttons to slots
    connect(Add, &QPushButton::clicked, this, &MainWindow::onAddStudentClicked);
    connect (Delete,&QPushButton::clicked, this, &MainWindow::onDeleteStudentClicked);
    connect(SearchandFilter, &QPushButton::clicked, this, &MainWindow::SearchFilterStudent);
    connect(Summaries, &QPushButton::clicked, this, &MainWindow::SummariesStudent);
}

MainWindow::~MainWindow()
{
    // Qt handles child widget deletion automatically
}

StudentBST *m_bst = new StudentBST();

void MainWindow::onAddStudentClicked()
{
    AddStudent *page1 = new AddStudent();
    page1->show();
}

void MainWindow::onDeleteStudentClicked()
{
    DeleteStudent *page2 = new DeleteStudent();
    page2->show();
}
void MainWindow::SearchFilterStudent()
{
    Search *page4 = new Search(m_bst);
    page4->show();
}
void MainWindow::SummariesStudent()
{
    ReportSummaries *page3 = new ReportSummaries(m_bst);
    page3->show();
}