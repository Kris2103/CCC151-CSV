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
    QPushButton *EditStudent;
    QPushButton *AddStudent;
    QPushButton *DeleteStudent;
    QPushButton *SaveStudent;
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
    QLabel *AddProgram;
    QLabel *AddCollege;
    QLineEdit *CollegeName;
    QLineEdit *ProgramCode_2;
    QLineEdit *ProgramName_2;
    QLineEdit *CollegeCodeProg;
    QLabel *ProgramCode;
    QLabel *ProgramName;
    QLabel *CollegeCode;
    QLabel *FirstName_5;
    QLabel *FirstName_6;
    QPushButton *AddProg;
    QPushButton *AddCollege_2;
    QPushButton *EditProg;
    QPushButton *Edit_3;
    QPushButton *Save_2;
    QPushButton *SaveProg;
    QComboBox *comboBox;
    QLabel *FirstName_7;
    QComboBox *comboBox_3;
    QLabel *FirstName_8;
    QLineEdit *CollegeCodeCol;
    QPushButton *SaveProg_2;
    QPushButton *SaveProg_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1123, 766);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Firstnameline = new QLineEdit(centralwidget);
        Firstnameline->setObjectName("Firstnameline");
        Firstnameline->setGeometry(QRect(90, 90, 301, 21));
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
        Genderline->setGeometry(QRect(90, 240, 141, 21));
        Genderline->setMinimumSize(QSize(141, 21));
        Genderline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        FirstName = new QLabel(centralwidget);
        FirstName->setObjectName("FirstName");
        FirstName->setGeometry(QRect(90, 70, 181, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("Rockwell")});
        font.setBold(true);
        font.setItalic(false);
        FirstName->setFont(font);
        Middlenameline = new QLineEdit(centralwidget);
        Middlenameline->setObjectName("Middlenameline");
        Middlenameline->setGeometry(QRect(90, 140, 301, 21));
        Middlenameline->setMinimumSize(QSize(301, 21));
        Middlenameline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        MiddleName = new QLabel(centralwidget);
        MiddleName->setObjectName("MiddleName");
        MiddleName->setGeometry(QRect(90, 120, 181, 20));
        MiddleName->setFont(font);
        Lastnameline = new QLineEdit(centralwidget);
        Lastnameline->setObjectName("Lastnameline");
        Lastnameline->setGeometry(QRect(90, 190, 301, 21));
        Lastnameline->setMinimumSize(QSize(301, 21));
        Lastnameline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        LastName = new QLabel(centralwidget);
        LastName->setObjectName("LastName");
        LastName->setGeometry(QRect(90, 170, 181, 20));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Rockwell")});
        font1.setBold(true);
        LastName->setFont(font1);
        Gender = new QLabel(centralwidget);
        Gender->setObjectName("Gender");
        Gender->setGeometry(QRect(90, 220, 141, 20));
        Gender->setFont(font1);
        YearLevel = new QLabel(centralwidget);
        YearLevel->setObjectName("YearLevel");
        YearLevel->setGeometry(QRect(250, 270, 141, 20));
        YearLevel->setFont(font1);
        Yearlevelline = new QComboBox(centralwidget);
        Yearlevelline->addItem(QString());
        Yearlevelline->addItem(QString());
        Yearlevelline->addItem(QString());
        Yearlevelline->addItem(QString());
        Yearlevelline->setObjectName("Yearlevelline");
        Yearlevelline->setGeometry(QRect(250, 290, 141, 21));
        Yearlevelline->setMinimumSize(QSize(141, 21));
        Yearlevelline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        IDnumber = new QLabel(centralwidget);
        IDnumber->setObjectName("IDnumber");
        IDnumber->setGeometry(QRect(250, 220, 141, 20));
        IDnumber->setFont(font1);
        IDline = new QLineEdit(centralwidget);
        IDline->setObjectName("IDline");
        IDline->setGeometry(QRect(250, 240, 141, 21));
        IDline->setMinimumSize(QSize(141, 21));
        IDline->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        StudentProfile = new QLabel(centralwidget);
        StudentProfile->setObjectName("StudentProfile");
        StudentProfile->setGeometry(QRect(90, 30, 301, 31));
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
        CourseCode->setGeometry(QRect(90, 270, 141, 20));
        CourseCode->setFont(font1);
        EditStudent = new QPushButton(centralwidget);
        EditStudent->setObjectName("EditStudent");
        EditStudent->setGeometry(QRect(90, 320, 91, 21));
        EditStudent->setMinimumSize(QSize(91, 20));
        EditStudent->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        AddStudent = new QPushButton(centralwidget);
        AddStudent->setObjectName("AddStudent");
        AddStudent->setGeometry(QRect(290, 320, 91, 21));
        AddStudent->setMinimumSize(QSize(91, 20));
        AddStudent->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        DeleteStudent = new QPushButton(centralwidget);
        DeleteStudent->setObjectName("DeleteStudent");
        DeleteStudent->setGeometry(QRect(190, 320, 91, 21));
        DeleteStudent->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:hover {\n"
"    background-color: #808080;\n"
"    border: 2px solid #2980b9;\n"
"}"));
        SaveStudent = new QPushButton(centralwidget);
        SaveStudent->setObjectName("SaveStudent");
        SaveStudent->setGeometry(QRect(290, 350, 91, 21));
        SaveStudent->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:hover {\n"
"    background-color: #808080;\n"
"    border: 2px solid #2980b9;\n"
"}"));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(440, 20, 671, 681));
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
        TabTable->setGeometry(QRect(10, 50, 661, 631));
        TabTable->setStyleSheet(QString::fromUtf8(""));
        tab = new QWidget();
        tab->setObjectName("tab");
        StudentTable = new QTableView(tab);
        StudentTable->setObjectName("StudentTable");
        StudentTable->setGeometry(QRect(10, 10, 641, 581));
        TabTable->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        ProgTable = new QTableView(tab_3);
        ProgTable->setObjectName("ProgTable");
        ProgTable->setGeometry(QRect(10, 10, 641, 581));
        TabTable->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        CollegeTable = new QTableView(tab_2);
        CollegeTable->setObjectName("CollegeTable");
        CollegeTable->setGeometry(QRect(10, 10, 641, 581));
        TabTable->addTab(tab_2, QString());
        Sort = new QComboBox(frame);
        Sort->addItem(QString());
        Sort->addItem(QString());
        Sort->setObjectName("Sort");
        Sort->setGeometry(QRect(110, 20, 101, 21));
        CourseComboBox = new QComboBox(centralwidget);
        CourseComboBox->setObjectName("CourseComboBox");
        CourseComboBox->setGeometry(QRect(90, 290, 141, 21));
        CourseComboBox->setMinimumSize(QSize(141, 21));
        CourseComboBox->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"	border: 2px solid #000000;\n"
"	border-radius: 5px;\n"
"	padding: 1px;\n"
"	box-shadow: 0 0 10px rgba(0,0,05);"));
        AddProgram = new QLabel(centralwidget);
        AddProgram->setObjectName("AddProgram");
        AddProgram->setGeometry(QRect(40, 380, 181, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Rockwell")});
        font3.setPointSize(12);
        font3.setBold(true);
        AddProgram->setFont(font3);
        AddProgram->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #800000;\n"
"    border-radius: 10px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);\n"
"    color: black;"));
        AddProgram->setAlignment(Qt::AlignmentFlag::AlignCenter);
        AddCollege = new QLabel(centralwidget);
        AddCollege->setObjectName("AddCollege");
        AddCollege->setGeometry(QRect(250, 380, 181, 31));
        AddCollege->setFont(font3);
        AddCollege->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"    border: 2px solid #800000;\n"
"    border-radius: 10px;\n"
"    padding: 1px;\n"
"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);\n"
"    color: black;"));
        AddCollege->setAlignment(Qt::AlignmentFlag::AlignCenter);
        CollegeName = new QLineEdit(centralwidget);
        CollegeName->setObjectName("CollegeName");
        CollegeName->setGeometry(QRect(250, 490, 181, 26));
        ProgramCode_2 = new QLineEdit(centralwidget);
        ProgramCode_2->setObjectName("ProgramCode_2");
        ProgramCode_2->setGeometry(QRect(40, 440, 181, 26));
        ProgramName_2 = new QLineEdit(centralwidget);
        ProgramName_2->setObjectName("ProgramName_2");
        ProgramName_2->setGeometry(QRect(40, 490, 181, 26));
        CollegeCodeProg = new QLineEdit(centralwidget);
        CollegeCodeProg->setObjectName("CollegeCodeProg");
        CollegeCodeProg->setGeometry(QRect(40, 540, 181, 26));
        ProgramCode = new QLabel(centralwidget);
        ProgramCode->setObjectName("ProgramCode");
        ProgramCode->setGeometry(QRect(40, 420, 111, 20));
        ProgramCode->setFont(font);
        ProgramName = new QLabel(centralwidget);
        ProgramName->setObjectName("ProgramName");
        ProgramName->setGeometry(QRect(40, 470, 121, 20));
        ProgramName->setFont(font);
        CollegeCode = new QLabel(centralwidget);
        CollegeCode->setObjectName("CollegeCode");
        CollegeCode->setGeometry(QRect(40, 520, 111, 20));
        CollegeCode->setFont(font);
        FirstName_5 = new QLabel(centralwidget);
        FirstName_5->setObjectName("FirstName_5");
        FirstName_5->setGeometry(QRect(250, 420, 111, 20));
        FirstName_5->setFont(font);
        FirstName_6 = new QLabel(centralwidget);
        FirstName_6->setObjectName("FirstName_6");
        FirstName_6->setGeometry(QRect(250, 470, 111, 20));
        FirstName_6->setFont(font);
        AddProg = new QPushButton(centralwidget);
        AddProg->setObjectName("AddProg");
        AddProg->setGeometry(QRect(140, 580, 91, 21));
        AddProg->setMinimumSize(QSize(91, 20));
        AddProg->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        AddCollege_2 = new QPushButton(centralwidget);
        AddCollege_2->setObjectName("AddCollege_2");
        AddCollege_2->setGeometry(QRect(350, 530, 91, 21));
        AddCollege_2->setMinimumSize(QSize(91, 20));
        AddCollege_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        EditProg = new QPushButton(centralwidget);
        EditProg->setObjectName("EditProg");
        EditProg->setGeometry(QRect(40, 580, 91, 21));
        EditProg->setMinimumSize(QSize(91, 20));
        EditProg->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        Edit_3 = new QPushButton(centralwidget);
        Edit_3->setObjectName("Edit_3");
        Edit_3->setGeometry(QRect(250, 530, 91, 21));
        Edit_3->setMinimumSize(QSize(91, 20));
        Edit_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        Save_2 = new QPushButton(centralwidget);
        Save_2->setObjectName("Save_2");
        Save_2->setGeometry(QRect(350, 560, 91, 21));
        Save_2->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:hover {\n"
"    background-color: #808080;\n"
"    border: 2px solid #2980b9;\n"
"}"));
        SaveProg = new QPushButton(centralwidget);
        SaveProg->setObjectName("SaveProg");
        SaveProg->setGeometry(QRect(140, 610, 81, 21));
        SaveProg->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:hover {\n"
"    background-color: #808080;\n"
"    border: 2px solid #2980b9;\n"
"}"));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(40, 650, 181, 26));
        FirstName_7 = new QLabel(centralwidget);
        FirstName_7->setObjectName("FirstName_7");
        FirstName_7->setGeometry(QRect(40, 630, 131, 20));
        FirstName_7->setFont(font);
        comboBox_3 = new QComboBox(centralwidget);
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(250, 600, 181, 26));
        FirstName_8 = new QLabel(centralwidget);
        FirstName_8->setObjectName("FirstName_8");
        FirstName_8->setGeometry(QRect(250, 580, 131, 20));
        FirstName_8->setFont(font);
        CollegeCodeCol = new QLineEdit(centralwidget);
        CollegeCodeCol->setObjectName("CollegeCodeCol");
        CollegeCodeCol->setGeometry(QRect(250, 440, 181, 26));
        SaveProg_2 = new QPushButton(centralwidget);
        SaveProg_2->setObjectName("SaveProg_2");
        SaveProg_2->setGeometry(QRect(140, 680, 81, 21));
        SaveProg_2->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:hover {\n"
"    background-color: #808080;\n"
"    border: 2px solid #2980b9;\n"
"}"));
        SaveProg_3 = new QPushButton(centralwidget);
        SaveProg_3->setObjectName("SaveProg_3");
        SaveProg_3->setGeometry(QRect(350, 630, 81, 21));
        SaveProg_3->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:hover {\n"
"    background-color: #808080;\n"
"    border: 2px solid #2980b9;\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1123, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        TabTable->setCurrentIndex(0);


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
        EditStudent->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        AddStudent->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        DeleteStudent->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        SaveStudent->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        Search->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        TabTable->setTabText(TabTable->indexOf(tab), QCoreApplication::translate("MainWindow", "Students", nullptr));
        TabTable->setTabText(TabTable->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Program", nullptr));
        TabTable->setTabText(TabTable->indexOf(tab_2), QCoreApplication::translate("MainWindow", "College", nullptr));
        Sort->setItemText(0, QCoreApplication::translate("MainWindow", "ID number", nullptr));
        Sort->setItemText(1, QCoreApplication::translate("MainWindow", "Lastname", nullptr));

        AddProgram->setText(QCoreApplication::translate("MainWindow", "Add Program", nullptr));
        AddCollege->setText(QCoreApplication::translate("MainWindow", "Add College", nullptr));
        ProgramCode->setText(QCoreApplication::translate("MainWindow", "Program Code", nullptr));
        ProgramName->setText(QCoreApplication::translate("MainWindow", "Program Name", nullptr));
        CollegeCode->setText(QCoreApplication::translate("MainWindow", "College Code", nullptr));
        FirstName_5->setText(QCoreApplication::translate("MainWindow", "College Code", nullptr));
        FirstName_6->setText(QCoreApplication::translate("MainWindow", "College Name", nullptr));
        AddProg->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        AddCollege_2->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        EditProg->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        Edit_3->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        Save_2->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        SaveProg->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        FirstName_7->setText(QCoreApplication::translate("MainWindow", "Delete Program", nullptr));
        FirstName_8->setText(QCoreApplication::translate("MainWindow", "Delete College", nullptr));
        SaveProg_2->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        SaveProg_3->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
