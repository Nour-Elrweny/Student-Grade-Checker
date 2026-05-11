#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddStudentClicked();
    void onDeleteStudentClicked();
    void SearchFilterStudent();
    void SummariesStudent();

private:
    QPushButton *Add;
    QPushButton *Delete;
    QPushButton *SearchandFilter;
    QPushButton *Summaries;
};

#endif // MAINWINDOW_H