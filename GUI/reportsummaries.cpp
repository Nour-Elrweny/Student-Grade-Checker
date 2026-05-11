#include "ReportSummaries.h"
#include <QLineEdit>
#include <QtWidgets>

ReportSummaries::ReportSummaries(StudentBST *bst,QWidget *parent)
    : QWidget(parent),m_bst(bst)
{
    setupUI();
    if (m_courseCombo->count() > 0)
        loadCourseData(m_courseCombo->currentText());
}

ReportSummaries::~ReportSummaries() {}

void ReportSummaries::setupUI()
{
    setFixedSize(800, 700);
    setStyleSheet("QWidget { background-color: #2b2b2b; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(60, 30, 60, 30);
    mainLayout->setSpacing(10);

    // ── Page Title ──────────────────────────────────────
    m_titleLabel = new QLabel("Reports & Summaries");
    m_titleLabel->setStyleSheet("QLabel { color: white; font-size: 24px; font-weight: bold; background: transparent; }");
    m_titleLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addSpacing(10);

    // ── Section Title ────────────────────────────────────
    m_courseSummaryLabel = createSectionTitle("Course Summary");
    mainLayout->addWidget(m_courseSummaryLabel);

    m_courseDescLabel = createLabel("Grade overview for all students in a course");
    mainLayout->addWidget(m_courseDescLabel);
    mainLayout->addSpacing(5);

    // ── Course Selector Row ──────────────────────────────
    mainLayout->addWidget(createLabel("Select Course"));

    QHBoxLayout *selectorRow = new QHBoxLayout();

    m_courseCombo = new QComboBox();
    m_courseCombo->setFixedHeight(38);
    m_courseCombo->addItem("Operating Systems (CSE 335s)");
    m_courseCombo->addItem("Data Structure and Algorithm (CSE 333s)");
    m_courseCombo->addItem("Machine Learning (CSE 374s)");
    m_courseCombo->setStyleSheet(
        "QComboBox {"
        "  background-color: #3c3f41;"
        "  color: white;"
        "  border: 1px solid #555;"
        "  border-radius: 6px;"
        "  padding: 0 10px;"
        "  font-size: 13px;"
        "}"
        "QComboBox:focus { border: 1px solid #3498db; }"
        "QComboBox QAbstractItemView {"
        "  background-color: #3c3f41;"
        "  color: white;"
        "  selection-background-color: #3498db;"
        "}"
        );

    m_loadButton = new QPushButton("↻ Load");
    m_loadButton->setFixedSize(100, 38);
    m_loadButton->setStyleSheet(
        "QPushButton { background-color: #3498db; color: white; border-radius: 8px; font-size: 13px; }"
        "QPushButton:hover { background-color: #2980b9; }"
        );

    selectorRow->addWidget(m_courseCombo);
    selectorRow->addSpacing(10);
    selectorRow->addWidget(m_loadButton);
    mainLayout->addLayout(selectorRow);
    mainLayout->addSpacing(10);

    // ── Stat Cards Row ───────────────────────────────────
    QHBoxLayout *statsRow = new QHBoxLayout();
    statsRow->setSpacing(10);
    statsRow->addWidget(createStatCard("Students Enrolled", m_enrolledValue));
    statsRow->addWidget(createStatCard("Class Average",     m_avgValue));
    statsRow->addWidget(createStatCard("Highest Grade",     m_highestValue));
    statsRow->addWidget(createStatCard("Failing (<50)",     m_failingValue));
    mainLayout->addLayout(statsRow);
    mainLayout->addSpacing(10);

    // ── Table ────────────────────────────────────────────
    m_allStudentsLabel = createSectionTitle("All Students");
    mainLayout->addWidget(m_allStudentsLabel);

    m_table = new QTableWidget();
    m_table->setColumnCount(5);
    m_table->setHorizontalHeaderLabels({"Student Name", "ID", "Grade (%)", "Letter", "Status"});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setVisible(false);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setStyleSheet(
        "QTableWidget {"
        "  background-color: #3c3f41;"
        "  color: white;"
        "  border: 1px solid #555;"
        "  border-radius: 6px;"
        "  font-size: 12px;"
        "  gridline-color: #555;"
        "}"
        "QHeaderView::section {"
        "  background-color: #2b2b2b;"
        "  color: #3498db;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "  border: 1px solid #555;"
        "  padding: 4px;"
        "}"
        "QTableWidget::item:selected {"
        "  background-color: #3498db;"
        "}"
        );
    mainLayout->addWidget(m_table);

    // ── Bottom Row ───────────────────────────────────────
    QHBoxLayout *bottomRow = new QHBoxLayout();

    m_statusLabel = new QLabel("Showing 0 of 0 students");
    m_statusLabel->setStyleSheet("QLabel { color: #aaaaaa; font-size: 11px; background: transparent; }");

    m_mainMenuButton = new QPushButton("← Main Menu");
    m_mainMenuButton->setFixedSize(150, 40);
    m_mainMenuButton->setStyleSheet(
        "QPushButton { background-color: #e74c3c; color: white; border-radius: 8px; font-size: 13px; }"
        "QPushButton:hover { background-color: #c0392b; }"
        );

    bottomRow->addWidget(m_statusLabel);
    bottomRow->addStretch();
    bottomRow->addWidget(m_mainMenuButton);
    mainLayout->addLayout(bottomRow);

    connect(m_loadButton,     &QPushButton::clicked, this, &ReportSummaries::onLoadClicked);
    connect(m_mainMenuButton, &QPushButton::clicked, this, &ReportSummaries::onMainMenuClicked);
}

// ── Stat Card Helper ──────────────────────────────────────
QWidget* ReportSummaries::createStatCard(const QString &title, QLabel *&valueLabel)
{
    QWidget *card = new QWidget();
    card->setFixedHeight(70);
    card->setStyleSheet(
        "QWidget {"
        "  background-color: #3c3f41;"
        "  border: 1px solid #555;"
        "  border-radius: 8px;"
        "}"
        );

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(4);

    QLabel *titleLbl = new QLabel(title);
    titleLbl->setStyleSheet("QLabel { color: #aaaaaa; font-size: 11px; border: none; background: transparent; }");
    titleLbl->setAlignment(Qt::AlignHCenter);

    valueLabel = new QLabel("0");
    valueLabel->setStyleSheet("QLabel { color: white; font-size: 20px; font-weight: bold; border: none; background: transparent; }");
    valueLabel->setAlignment(Qt::AlignHCenter);

    layout->addWidget(titleLbl);
    layout->addWidget(valueLabel);

    return card;
}

// ── Helpers ───────────────────────────────────────────────
QLabel* ReportSummaries::createSectionTitle(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setStyleSheet(
        "QLabel {"
        "  color: #3498db;"
        "  font-size: 15px;"
        "  font-weight: bold;"
        "  border-bottom: 1px solid #3498db;"
        "  padding-bottom: 4px;"
        "  background: transparent;"
        "}"
        );
    return label;
}

QLabel* ReportSummaries::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setStyleSheet("QLabel { color: #aaaaaa; font-size: 12px; background: transparent; }");
    return label;
}

// ── Slots ─────────────────────────────────────────────────
void ReportSummaries::onLoadClicked()
{
    loadCourseData(m_courseCombo->currentText());
}

  void ReportSummaries::loadCourseData(const QString &courseName)
    {
        // Sample data – replace with real backend calls
        if (courseName == "Operating Systems (CSE 335s)")
        {
            m_enrolledValue->setText("32");
            m_avgValue->setText("78.4");
            m_highestValue->setText("98");
            m_failingValue->setText("5");

            m_table->setRowCount(5);
            m_table->setItem(0, 0, new QTableWidgetItem("Alice Johnson"));
            m_table->setItem(0, 1, new QTableWidgetItem("S12345"));
            m_table->setItem(0, 2, new QTableWidgetItem("85.5"));
            m_table->setItem(0, 3, new QTableWidgetItem("B"));
            m_table->setItem(0, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(1, 0, new QTableWidgetItem("Amany Amr"));
            m_table->setItem(1, 1, new QTableWidgetItem("S23456"));
            m_table->setItem(1, 2, new QTableWidgetItem("92.0"));
            m_table->setItem(1, 3, new QTableWidgetItem("A-"));
            m_table->setItem(1, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(2, 0, new QTableWidgetItem("Sama Alaa"));
            m_table->setItem(2, 1, new QTableWidgetItem("S34567"));
            m_table->setItem(2, 2, new QTableWidgetItem("45.0"));
            m_table->setItem(2, 3, new QTableWidgetItem("F"));
            m_table->setItem(2, 4, new QTableWidgetItem("Fail"));

            m_table->setItem(3, 0, new QTableWidgetItem("David Wilson"));
            m_table->setItem(3, 1, new QTableWidgetItem("S45678"));
            m_table->setItem(3, 2, new QTableWidgetItem("76.2"));
            m_table->setItem(3, 3, new QTableWidgetItem("C+"));
            m_table->setItem(3, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(4, 0, new QTableWidgetItem("Emma Brown"));
            m_table->setItem(4, 1, new QTableWidgetItem("S56789"));
            m_table->setItem(4, 2, new QTableWidgetItem("98.0"));
            m_table->setItem(4, 3, new QTableWidgetItem("A+"));
            m_table->setItem(4, 4, new QTableWidgetItem("Pass"));

            m_statusLabel->setText("Showing 5 of 32 students");
        }
        else if (courseName == "Data Structure and Algorithm (CSE 333s)")
        {
            m_enrolledValue->setText("28");
            m_avgValue->setText("82.1");
            m_highestValue->setText("100");
            m_failingValue->setText("2");

            m_table->setRowCount(5);
            m_table->setItem(0, 0, new QTableWidgetItem("Mirium George"));
            m_table->setItem(0, 1, new QTableWidgetItem("2300888"));
            m_table->setItem(0, 2, new QTableWidgetItem("91.0"));
            m_table->setItem(0, 3, new QTableWidgetItem("A-"));
            m_table->setItem(0, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(1, 0, new QTableWidgetItem("Nouran Awad"));
            m_table->setItem(1, 1, new QTableWidgetItem("2300555"));
            m_table->setItem(1, 2, new QTableWidgetItem("67.5"));
            m_table->setItem(1, 3, new QTableWidgetItem("D+"));
            m_table->setItem(1, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(2, 0, new QTableWidgetItem("Mariam Ahmed"));
            m_table->setItem(2, 1, new QTableWidgetItem("2300777"));
            m_table->setItem(2, 2, new QTableWidgetItem("100.0"));
            m_table->setItem(2, 3, new QTableWidgetItem("A+"));
            m_table->setItem(2, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(3, 0, new QTableWidgetItem("George Smith"));
            m_table->setItem(3, 1, new QTableWidgetItem("S90123"));
            m_table->setItem(3, 2, new QTableWidgetItem("48.0"));
            m_table->setItem(3, 3, new QTableWidgetItem("F"));
            m_table->setItem(3, 4, new QTableWidgetItem("Fail"));

            m_table->setItem(4, 0, new QTableWidgetItem("Malak Ehab"));
            m_table->setItem(4, 1, new QTableWidgetItem("S01234"));
            m_table->setItem(4, 2, new QTableWidgetItem("79.3"));
            m_table->setItem(4, 3, new QTableWidgetItem("C+"));
            m_table->setItem(4, 4, new QTableWidgetItem("Pass"));

            m_statusLabel->setText("Showing 5 of 28 students");
        }
        else if (courseName == "Machine Learning (CSE 374s)")
        {
            m_enrolledValue->setText("25");
            m_avgValue->setText("88.6");
            m_highestValue->setText("99");
            m_failingValue->setText("1");

            m_table->setRowCount(5);
            m_table->setItem(0, 0, new QTableWidgetItem("Kevin Wang"));
            m_table->setItem(0, 1, new QTableWidgetItem("S12378"));
            m_table->setItem(0, 2, new QTableWidgetItem("94.0"));
            m_table->setItem(0, 3, new QTableWidgetItem("A"));
            m_table->setItem(0, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(1, 0, new QTableWidgetItem("Lisa Kim"));
            m_table->setItem(1, 1, new QTableWidgetItem("S23489"));
            m_table->setItem(1, 2, new QTableWidgetItem("87.5"));
            m_table->setItem(1, 3, new QTableWidgetItem("B+"));
            m_table->setItem(1, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(2, 0, new QTableWidgetItem("Mostafa Said"));
            m_table->setItem(2, 1, new QTableWidgetItem("S34590"));
            m_table->setItem(2, 2, new QTableWidgetItem("99.0"));
            m_table->setItem(2, 3, new QTableWidgetItem("A+"));
            m_table->setItem(2, 4, new QTableWidgetItem("Pass"));

            m_table->setItem(3, 0, new QTableWidgetItem("Yahia Amad"));
            m_table->setItem(3, 1, new QTableWidgetItem("S45601"));
            m_table->setItem(3, 2, new QTableWidgetItem("42.0"));
            m_table->setItem(3, 3, new QTableWidgetItem("F"));
            m_table->setItem(3, 4, new QTableWidgetItem("Fail"));

            m_table->setItem(4, 0, new QTableWidgetItem("Youssef Ahmed"));
            m_table->setItem(4, 1, new QTableWidgetItem("S56712"));
            m_table->setItem(4, 2, new QTableWidgetItem("91.2"));
            m_table->setItem(4, 3, new QTableWidgetItem("A-"));
            m_table->setItem(4, 4, new QTableWidgetItem("Pass"));

            m_statusLabel->setText("Showing 5 of 25 students");
        }
        else
        {
            m_enrolledValue->setText("0");
            m_avgValue->setText("0");
            m_highestValue->setText("0");
            m_failingValue->setText("0");
            m_table->setRowCount(0);
            m_statusLabel->setText("Showing 0 of 0 students");
        }
    }



void ReportSummaries::onMainMenuClicked()
{
    close();
}