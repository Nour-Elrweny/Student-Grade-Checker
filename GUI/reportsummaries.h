#ifndef REPORTSUMMARIES_H
#define REPORTSUMMARIES_H

#include "StudentBST.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

class ReportSummaries : public QWidget
{
    Q_OBJECT

public:
    ReportSummaries(StudentBST *bst,QWidget *parent = nullptr);
    ~ReportSummaries();

signals:
    void goBack();

private slots:
    void onLoadClicked();
    void onMainMenuClicked();

private:
    QLabel        *m_titleLabel;
    QLabel        *m_courseSummaryLabel;
    QLabel        *m_courseDescLabel;
    QLabel        *m_selectCourseLabel;
    QLabel        *m_allStudentsLabel;
    QLabel        *m_statusLabel;
    QComboBox     *m_courseCombo;
    QPushButton   *m_loadButton;
    QPushButton   *m_mainMenuButton;
    QTableWidget  *m_table;

     StudentBST* m_bst;

    // Stat frames
    QLabel *m_enrolledValue;
    QLabel *m_avgValue;
    QLabel *m_highestValue;
    QLabel *m_failingValue;

    void setupUI();
    void loadCourseData(const QString &courseName);

    // Helpers
    QLineEdit*  createInput(const QString &placeholder);
    QLabel*     createSectionTitle(const QString &text);
    QLabel*     createLabel(const QString &text);
    QWidget*    createStatCard(const QString &title, QLabel *&valueLabel);
};

#endif // REPORTSUMMARIES_H