#include "search.h"
#include "studentBST.h"
#include <QtWidgets>

Search::Search(StudentBST *bst,QWidget *parent)
    : QWidget(parent),m_bst(bst)
{
    m_bst->addStudent(Student(2300949, "Nour Khaled", "CS"));
    m_bst->addStudent(Student(2300555, "Mirium George", "EE"));

    setupUI();
    updateResults("");
}

Search::~Search() {}

void Search::setupUI()
{
    setFixedSize(800, 700);
    setStyleSheet("QWidget { background-color: #2b2b2b; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(60, 30, 60, 30);
    mainLayout->setSpacing(10);

    // ── Page Title ──────────────────────────────────────
    m_titleLabel = new QLabel("Search Students");
    m_titleLabel->setStyleSheet("QLabel { color: white; font-size: 24px; font-weight: bold; background: transparent; }");
    m_titleLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addSpacing(10);

    // ── Section Title ────────────────────────────────────
    mainLayout->addWidget(createSectionTitle("Search Students"));
    mainLayout->addWidget(createLabel("Find records by ID"));
    mainLayout->addSpacing(5);

    // ── Search Bar Row ───────────────────────────────────
    QHBoxLayout *searchRow = new QHBoxLayout();

    m_searchLine = new QLineEdit();
    m_searchLine->setPlaceholderText("Search by ID...");
    m_searchLine->setFixedHeight(38);
    m_searchLine->setStyleSheet(
        "QLineEdit {"
        "  background-color: #3c3f41;"
        "  color: white;"
        "  border: 1px solid #555;"
        "  border-radius: 6px;"
        "  padding: 0 10px;"
        "  font-size: 13px;"
        "}"
        "QLineEdit:focus { border: 1px solid #3498db; }"
        );

    m_filterBtn = new QPushButton("≡ Filters");
    m_filterBtn->setFixedSize(100, 38);
    m_filterBtn->setStyleSheet(
        "QPushButton { background-color: #3498db; color: white; border-radius: 8px; font-size: 13px; }"
        "QPushButton:hover { background-color: #2980b9; }"
        );

    searchRow->addWidget(m_searchLine);
    searchRow->addSpacing(10);
    searchRow->addWidget(m_filterBtn);
    mainLayout->addLayout(searchRow);
    mainLayout->addSpacing(5);

    // ── Result Count ─────────────────────────────────────
    m_resultCountLabel = createLabel("Showing 0 results");
    mainLayout->addWidget(m_resultCountLabel);
    mainLayout->addSpacing(5);

    // ── Result Cards Container ───────────────────────────
    m_cardsContainer = new QWidget();
    m_cardsContainer->setStyleSheet("QWidget { background-color: transparent; }");
    m_cardsLayout = new QVBoxLayout(m_cardsContainer);
    m_cardsLayout->setSpacing(8);
    m_cardsLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 4; ++i)
        m_cardsLayout->addWidget(createResultCard(m_resultFrames[i]));

    mainLayout->addWidget(m_cardsContainer);
    mainLayout->addStretch();

    // ── Bottom Row ───────────────────────────────────────
    QHBoxLayout *bottomRow = new QHBoxLayout();

    m_mainMenuBtn = new QPushButton("← Main Menu");
    m_mainMenuBtn->setFixedSize(150, 40);
    m_mainMenuBtn->setStyleSheet(
        "QPushButton { background-color: #e74c3c; color: white; border-radius: 8px; font-size: 13px; }"
        "QPushButton:hover { background-color: #c0392b; }"
        );

    bottomRow->addStretch();
    bottomRow->addWidget(m_mainMenuBtn);
    mainLayout->addLayout(bottomRow);

    connect(m_searchLine,  &QLineEdit::textChanged,   this, &Search::onSearchTextChanged);
    connect(m_filterBtn,   &QPushButton::clicked,     this, &Search::onFilterClicked);
    connect(m_mainMenuBtn, &QPushButton::clicked,     this, &Search::onMainMenuClicked);
}

// ── Result Card Helper ────────────────────────────────────
QWidget* Search::createResultCard(ResultCard &card)
{
    QWidget *cardWidget = new QWidget();
    cardWidget->setFixedHeight(70);
    cardWidget->setStyleSheet(
        "QWidget {"
        "  background-color: #3c3f41;"
        "  border: 1px solid #555;"
        "  border-radius: 8px;"
        "}"
        );

    QHBoxLayout *layout = new QHBoxLayout(cardWidget);
    layout->setContentsMargins(15, 10, 15, 10);
    layout->setSpacing(10);

    // Avatar
    QLabel *avatar = new QLabel("👤");
    avatar->setFixedSize(110, 45);
    avatar->setStyleSheet("QLabel { font-size: 28px; background: transparent; border: none; }");
    avatar->setAlignment(Qt::AlignCenter);

    // Name + ID row
    QWidget *infoWidget = new QWidget();
    infoWidget->setStyleSheet("QWidget { background: transparent; }");
    QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
    infoLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->setSpacing(2);

    card.name = new QLabel("Student Name");
    card.name->setStyleSheet("QLabel { color: white; font-size: 13px; font-weight: bold; background: transparent; border: none; }");

    QHBoxLayout *subRow = new QHBoxLayout();
    card.id = new QLabel("ID: -----");
    card.id->setStyleSheet("QLabel { color: #aaaaaa; font-size: 13px; background: transparent; border: none; }");
    card.dept = new QLabel("---");
    card.dept->setStyleSheet("QLabel { color: #aaaaaa; font-size: 13px; background: transparent; border: none; }");
    subRow->addWidget(card.id);
    subRow->addSpacing(10);
    subRow->addWidget(card.dept);
    subRow->addStretch();

    infoLayout->addWidget(card.name);
    infoLayout->addLayout(subRow);

    // GPA
    card.gpa = new QLabel("GPA");
    card.gpa->setStyleSheet("QLabel { color: #2ecc71; font-size: 13px; font-weight: bold; background: transparent; border: none; }");
    card.gpa->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    card.card = cardWidget;

    layout->addWidget(avatar);
    layout->addWidget(infoWidget);
    layout->addStretch();
    layout->addWidget(card.gpa);

    return cardWidget;
}

// ── Helpers ───────────────────────────────────────────────
QLabel* Search::createSectionTitle(const QString &text)
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

QLabel* Search::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setStyleSheet("QLabel { color: #aaaaaa; font-size: 12px; background: transparent; }");
    return label;
}


void Search::updateResults(const QString &searchId)
{
    // Step 1: create empty results list
    QVector<StudentInfo> matches;

    // Step 2: if box is empty show nothing, otherwise search
    if (searchId.isEmpty()) {
        vector<Student> all;
        m_bst->getAllStudents(all);

        // convert each Student to StudentInfo for the UI
        for (const Student& s : all) {
            StudentInfo info;
            info.name       = QString::fromStdString(s.getName());
            info.id         = QString::number(s.getId());
            info.department = QString::fromStdString(s.getDept());
            info.gpa        = "";
            matches.append(info);
        }
    } else {

        // Step 3: convert what the user typed from QString to int
        // because your backend takes an int ID
        bool ok;
        int id = searchId.toInt(&ok);

        // Step 4: ok will be false if the user typed letters instead of numbers
        if (ok) {

            // Step 5: call YOUR backend with the id
            Student *result = m_bst->searchById(id);

            // Step 6: if a student was found (not nullptr)
            if (result != nullptr) {
                StudentInfo info;
                info.name       = QString::fromStdString(result->getName());
                info.id         = QString::number(result->getId());
                info.department = QString::fromStdString(result->getDept());

                matches.append(info);
            }
        }
    }

    // Step 9: update the "Showing X results" label — stays the same
    m_resultCountLabel->setText(QString("Showing %1 result%2")
                                    .arg(matches.size())
                                    .arg(matches.size() == 1 ? "" : "s"));

    // Step 10: fill or hide the 4 cards — stays the same
    for (int i = 0; i < 4; ++i) {
        if (i < matches.size()) {
            const StudentInfo &stu = matches[i];
            m_resultFrames[i].name->setText(stu.name);
            m_resultFrames[i].id->setText("ID: " + stu.id);
            m_resultFrames[i].dept->setText(stu.department);
            m_resultFrames[i].gpa->setText(stu.gpa);
            m_resultFrames[i].card->show();
        } else {
            m_resultFrames[i].card->hide();
        }
    }
}
// ── Slots ─────────────────────────────────────────────────
void Search::onSearchTextChanged(const QString &text) { updateResults(text); }

void Search::onFilterClicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle("Filter by Department");
    dialog.setLabelText("Select Department:");
    dialog.setComboBoxItems({"CS", "EE", "ME", "CE"});
    dialog.setComboBoxEditable(false);
    dialog.setStyleSheet(
        "QInputDialog {"
        "  background-color: #2b2b2b;"
        "}"
        "QLabel {"
        "  color: white;"
        "  font-size: 13px;"
        "}"
        "QComboBox {"
        "  background-color: #3c3f41;"
        "  color: white;"
        "  border: 1px solid #555;"
        "  border-radius: 6px;"
        "  padding: 0 10px;"
        "  font-size: 13px;"
        "}"
        "QComboBox QAbstractItemView {"
        "  background-color: #3c3f41;"
        "  color: white;"
        "  selection-background-color: #3498db;"
        "}"
        "QPushButton {"
        "  background-color: #3498db;"
        "  color: white;"
        "  border-radius: 6px;"
        "  padding: 5px 15px;"
        "  font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #2980b9;"
        "}"
        );

    if (dialog.exec() == QDialog::Accepted) {
        QString dept = dialog.textValue();


        std::vector<Student> filtered;
        m_bst->filterByDept(dept.toStdString(), filtered);

        // convert to UI cards
        QVector<StudentInfo> matches;
        for (const Student &s : filtered) {
            StudentInfo info;
            info.name       = QString::fromStdString(s.getName());
            info.id         = QString::number(s.getId());
            info.department = QString::fromStdString(s.getDept());
            info.gpa        = "";
            matches.append(info);
        }

        // update label and cards
        m_resultCountLabel->setText(QString("Showing %1 result%2")
                                        .arg(matches.size())
                                        .arg(matches.size() == 1 ? "" : "s"));

        for (int i = 0; i < 4; ++i) {
            if (i < matches.size()) {
                m_resultFrames[i].name->setText(matches[i].name);
                m_resultFrames[i].id->setText("ID: " + matches[i].id);
                m_resultFrames[i].dept->setText(matches[i].department);
                m_resultFrames[i].card->show();
            } else {
                m_resultFrames[i].card->hide();
            }
        }
    }}

void Search::onMainMenuClicked() { close(); }