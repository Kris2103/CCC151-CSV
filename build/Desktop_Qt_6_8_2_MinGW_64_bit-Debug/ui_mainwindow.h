/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *Firstnameline;
    QComboBox *Genderline;
    QLabel *FirstName;
    QLineEdit *Middlenameline;
    QLabel *MiddleName;
    QLineEdit *Lastnameline;
    QLabel *LastName;
    QLabel *Gender;
    QLabel *YearLevel;
    QComboBox *Yearlevelline;
    QLabel *IDnumber;
    QLineEdit *IDline;
    QLabel *StudentProfile;
    QLabel *CourseCode;
    QPushButton *Edit;
    QPushButton *Add;
    QPushButton *Delete;
    QPushButton *Save;
    QFrame *frame;
    QLineEdit *SearchLine;
    QPushButton *Search;
    QTabWidget *TabTable;
    QWidget *tab;
    QTableView *StudentTable;
    QWidget *tab_3;
    QTableView *ProgTable;
    QWidget *tab_2;
    QTableView *CollegeTable;
    QComboBox *Sort;
    QComboBox *CourseComboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 530);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Firstnameline = new QLineEdit(centralwidget);
        Firstnameline->setObjectName("Firstnameline");
        Firstnameline->setGeometry(QRect(50, 150, 301, 21));
        Firstnameline->setMinimumSize(QSize(301, 21));
        Firstnameline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        Genderline = new QComboBox(centralwidget);
        Genderline->addItem(QString());
        Genderline->addItem(QString());
        Genderline->setObjectName("Genderline");
        Genderline->setGeometry(QRect(50, 300, 141, 21));
        Genderline->setMinimumSize(QSize(141, 21));
        Genderline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        FirstName = new QLabel(centralwidget);
        FirstName->setObjectName("FirstName");
        FirstName->setGeometry(QRect(50, 130, 181, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("Rockwell")});
        font.setBold(true);
        font.setItalic(false);
        FirstName->setFont(font);
        Middlenameline = new QLineEdit(centralwidget);
        Middlenameline->setObjectName("Middlenameline");
        Middlenameline->setGeometry(QRect(50, 200, 301, 21));
        Middlenameline->setMinimumSize(QSize(301, 21));
        Middlenameline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        MiddleName = new QLabel(centralwidget);
        MiddleName->setObjectName("MiddleName");
        MiddleName->setGeometry(QRect(50, 180, 181, 20));
        MiddleName->setFont(font);
        Lastnameline = new QLineEdit(centralwidget);
        Lastnameline->setObjectName("Lastnameline");
        Lastnameline->setGeometry(QRect(50, 250, 301, 21));
        Lastnameline->setMinimumSize(QSize(301, 21));
        Lastnameline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        LastName = new QLabel(centralwidget);
        LastName->setObjectName("LastName");
        LastName->setGeometry(QRect(50, 230, 181, 20));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Rockwell")});
        font1.setBold(true);
        LastName->setFont(font1);
        Gender = new QLabel(centralwidget);
        Gender->setObjectName("Gender");
        Gender->setGeometry(QRect(50, 280, 141, 20));
        Gender->setFont(font1);
        YearLevel = new QLabel(centralwidget);
        YearLevel->setObjectName("YearLevel");
        YearLevel->setGeometry(QRect(210, 330, 141, 20));
        YearLevel->setFont(font1);
        Yearlevelline = new QComboBox(centralwidget);
        Yearlevelline->addItem(QString());
        Yearlevelline->addItem(QString());
        Yearlevelline->addItem(QString());
        Yearlevelline->addItem(QString());
        Yearlevelline->setObjectName("Yearlevelline");
        Yearlevelline->setGeometry(QRect(210, 350, 141, 21));
        Yearlevelline->setMinimumSize(QSize(141, 21));
        Yearlevelline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        IDnumber = new QLabel(centralwidget);
        IDnumber->setObjectName("IDnumber");
        IDnumber->setGeometry(QRect(210, 280, 141, 20));
        IDnumber->setFont(font1);
        IDline = new QLineEdit(centralwidget);
        IDline->setObjectName("IDline");
        IDline->setGeometry(QRect(210, 300, 141, 21));
        IDline->setMinimumSize(QSize(141, 21));
        IDline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        StudentProfile = new QLabel(centralwidget);
        StudentProfile->setObjectName("StudentProfile");
        StudentProfile->setGeometry(QRect(70, 90, 261, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Rockwell")});
        font2.setPointSize(20);
        font2.setBold(true);
        StudentProfile->setFont(font2);
        StudentProfile->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #800000;\n"
"    border-radius: 10px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);\n"
"    color: black;"));
        StudentProfile->setAlignment(Qt::AlignmentFlag::AlignCenter);
        CourseCode = new QLabel(centralwidget);
        CourseCode->setObjectName("CourseCode");
        CourseCode->setGeometry(QRect(50, 330, 141, 20));
        CourseCode->setFont(font1);
        Edit = new QPushButton(centralwidget);
        Edit->setObjectName("Edit");
        Edit->setGeometry(QRect(50, 390, 91, 21));
        Edit->setMinimumSize(QSize(91, 20));
        Edit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #800000;\n"
"    color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"     padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);\n"
"    color: white; \n"
"}\n"
"\n"
"/ Hover effect for the button */\n"
"QPushButton:hover {\n"
"    background-color: #944E63;\n"
"    border: 2px solid #944E63;\n"
"}"));
        Add = new QPushButton(centralwidget);
        Add->setObjectName("Add");
        Add->setGeometry(QRect(250, 390, 91, 21));
        Add->setMinimumSize(QSize(91, 20));
        Add->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #800000;\n"
"    color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"     padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);\n"
"    color: white; \n"
"}\n"
"\n"
"/ Hover effect for the button */\n"
"QPushButton:hover {\n"
"    background-color: #944E63;\n"
"    border: 2px solid #944E63;\n"
"}"));
        Delete = new QPushButton(centralwidget);
        Delete->setObjectName("Delete");
        Delete->setGeometry(QRect(150, 390, 91, 21));
        Delete->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:hover {\n"
"    background-color: #808080;\n"
"    border: 2px solid #2980b9;\n"
"}"));
        Save = new QPushButton(centralwidget);
        Save->setObjectName("Save");
        Save->setGeometry(QRect(250, 420, 91, 21));
        Save->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:hover {\n"
"    background-color: #808080;\n"
"    border: 2px solid #2980b9;\n"
"}"));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(370, 20, 651, 491));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        SearchLine = new QLineEdit(frame);
        SearchLine->setObjectName("SearchLine");
        SearchLine->setGeometry(QRect(220, 20, 301, 21));
        SearchLine->setMinimumSize(QSize(301, 21));
        SearchLine->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        Search = new QPushButton(frame);
        Search->setObjectName("Search");
        Search->setGeometry(QRect(530, 20, 91, 20));
        Search->setMinimumSize(QSize(91, 20));
        Search->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #800000;\n"
"    color: white;\n"
"    border: 2px solid #000000;\n"
"    border-radius: 5px;\n"
"     padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);\n"
"    color: white; \n"
"}\n"
"\n"
"/ Hover effect for the button */\n"
"QPushButton:hover {\n"
"    background-color: #944E63;\n"
"    border: 2px solid #944E63;\n"
"}"));
        TabTable = new QTabWidget(frame);
        TabTable->setObjectName("TabTable");
        TabTable->setGeometry(QRect(20, 50, 611, 411));
        TabTable->setStyleSheet(QString::fromUtf8(""));
        tab = new QWidget();
        tab->setObjectName("tab");
        StudentTable = new QTableView(tab);
        StudentTable->setObjectName("StudentTable");
        StudentTable->setGeometry(QRect(10, 10, 611, 401));
        TabTable->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        ProgTable = new QTableView(tab_3);
        ProgTable->setObjectName("ProgTable");
        ProgTable->setGeometry(QRect(10, 10, 601, 411));
        TabTable->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        CollegeTable = new QTableView(tab_2);
        CollegeTable->setObjectName("CollegeTable");
        CollegeTable->setGeometry(QRect(10, 10, 601, 381));
        TabTable->addTab(tab_2, QString());
        Sort = new QComboBox(frame);
        Sort->addItem(QString());
        Sort->addItem(QString());
        Sort->setObjectName("Sort");
        Sort->setGeometry(QRect(110, 20, 101, 21));
        CourseComboBox = new QComboBox(centralwidget);
        CourseComboBox->setObjectName("CourseComboBox");
        CourseComboBox->setGeometry(QRect(50, 350, 141, 21));
        CourseComboBox->setMinimumSize(QSize(141, 21));
        CourseComboBox->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        TabTable->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Genderline->setItemText(0, QCoreApplication::translate("MainWindow", "Male", nullptr));
        Genderline->setItemText(1, QCoreApplication::translate("MainWindow", "Female", nullptr));

        FirstName->setText(QCoreApplication::translate("MainWindow", "First Name", nullptr));
        MiddleName->setText(QCoreApplication::translate("MainWindow", "Middle Name", nullptr));
        LastName->setText(QCoreApplication::translate("MainWindow", "Last Name", nullptr));
        Gender->setText(QCoreApplication::translate("MainWindow", "Gender", nullptr));
        YearLevel->setText(QCoreApplication::translate("MainWindow", "Year Level", nullptr));
        Yearlevelline->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        Yearlevelline->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        Yearlevelline->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));
        Yearlevelline->setItemText(3, QCoreApplication::translate("MainWindow", "4", nullptr));

        IDnumber->setText(QCoreApplication::translate("MainWindow", "I.D. Number", nullptr));
        IDline->setPlaceholderText(QCoreApplication::translate("MainWindow", "e.g. 2000-0000", nullptr));
        StudentProfile->setText(QCoreApplication::translate("MainWindow", "Student Profile", nullptr));
        CourseCode->setText(QCoreApplication::translate("MainWindow", "Course Code", nullptr));
        Edit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        Add->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        Delete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        Save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        Search->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        TabTable->setTabText(TabTable->indexOf(tab), QCoreApplication::translate("MainWindow", "Students", nullptr));
        TabTable->setTabText(TabTable->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Program", nullptr));
        TabTable->setTabText(TabTable->indexOf(tab_2), QCoreApplication::translate("MainWindow", "College", nullptr));
        Sort->setItemText(0, QCoreApplication::translate("MainWindow", "ID number", nullptr));
        Sort->setItemText(1, QCoreApplication::translate("MainWindow", "Lastname", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
