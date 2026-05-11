#ifndef SEARCH_H
#define SEARCH_H

#include "studentBST.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>

struct StudentInfo {
    QString name;
    QString id;
    QString department;
    QString gpa;
};

struct ResultCard {
    QWidget *card;
    QLabel  *name;
    QLabel  *id;
    QLabel  *dept;
    QLabel  *gpa;
};

class Search : public QWidget
{
    Q_OBJECT

public:
    Search(StudentBST *bst,QWidget *parent = nullptr);
    ~Search();

signals:
    void goBack();

private slots:
    void onSearchTextChanged(const QString &text);
    void onFilterClicked();
    void onMainMenuClicked();

private:
    QLabel      *m_titleLabel;
    QLabel      *m_resultCountLabel;
    QLineEdit   *m_searchLine;
    QPushButton *m_filterBtn;
    QPushButton *m_mainMenuBtn;

    QVBoxLayout *m_cardsLayout;
    QWidget     *m_cardsContainer;

    ResultCard m_resultFrames[4];

    QVector<StudentInfo> m_allStudents;
    StudentBST *m_bst;

    void setupUI();
    void populateSampleStudents();
    void updateResults(const QString &searchId);

    QLabel*  createLabel(const QString &text);
    QLabel*  createSectionTitle(const QString &text);
    QWidget* createResultCard(ResultCard &card);
};

#endif // SEARCH_H