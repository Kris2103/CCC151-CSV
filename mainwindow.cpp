#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QModelIndex>
#include <QStandardItem>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QTableView>
#include <QSortFilterProxyModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    studentModel = new QStandardItemModel(this);
    programModel = new QStandardItemModel(this);
    collegeModel = new QStandardItemModel(this);
    studentProxyModel = new QSortFilterProxyModel(this);

    loadCSVStudents("C:/Users/Kristelle/Documents/BSCS-3/CCC151 - Database Management/CSV Project/CSV1/Student.csv");
    loadCSVProgram("C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CSV Project//CSV1//Program.csv");
    loadCSVCollege("C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CSV Project//CSV1//College.csv");

    ui->StudentTable->setModel(studentModel);
    ui->StudentTable->resizeColumnsToContents();
    ui->ProgTable->setModel(programModel);
    ui->ProgTable->resizeColumnsToContents();
    ui->CollegeTable->setModel(collegeModel);
    ui->CollegeTable->resizeColumnsToContents();

    studentModel->setHorizontalHeaderLabels({"I.D. Number", "Last Name", "First Name", "Middle Name", "Gender", "Year Level", "Course"});
    programModel->setHorizontalHeaderLabels({"Program", "Program Name", "College Code"});
    collegeModel->setHorizontalHeaderLabels({"College Name", "College Code"});

    studentProxyModel->setSourceModel(studentModel);
    studentProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    studentProxyModel->setSortRole(Qt::DisplayRole);

    // Connect ComboBox selection change to sorting function
    connect(ui->Sort, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::sortStudents);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete studentModel;
    delete programModel;
    delete collegeModel;

}

void MainWindow::loadCSVStudents(const QString &filePath)
{
    studentModel->clear();

    currentCSVStudent = filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd())
        {
            QString value = in.readLine();
            QStringList rLine = value.split(',');

            studentModel->appendRow({});

            for (int i = 0; i < rLine.size(); i++)
            {
                QString value = rLine.at(i);
                QStandardItem *item = new QStandardItem(value);

                item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                studentModel->setItem(row, i, item);
            }
            row++;
        }
        file.close();
    }
    studentModel->setHorizontalHeaderLabels({"I.D. Number", "Last Name", "First Name", "Middle Name", "Gender", "Year Level", "Course"});
}

void MainWindow::loadCSVProgram(const QString &filePath)
{
    programModel->clear();
    ui->CourseComboBox->clear();
    currentCSVProgram = filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd())
        {
            QString value = in.readLine();
            QStringList rLine = value.split(',');

            if (rLine.size() > 1) // Assuming second column contains course name
            {
                ui->CourseComboBox->addItem(rLine.at(0)); // Add course to ComboBox
            }

            programModel->appendRow({});

            for (int i = 0; i < rLine.size(); i++)
            {
                QString value = rLine.at(i);
                QStandardItem *item = new QStandardItem(value);

                item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                programModel->setItem(row, i, item);
            }
            row++;
        }
        file.close();
    }
    programModel->setHorizontalHeaderLabels({"Program", "Program Name", "College Code"});
}
void MainWindow::loadCSVCollege(const QString &filePath)
{
    collegeModel->clear();

    currentCSVCollege = filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd())
        {
            QString value = in.readLine();
            QStringList rLine = value.split(',');

            collegeModel->appendRow({});

            for (int i = 0; i < rLine.size(); i++)
            {
                QString value = rLine.at(i);
                QStandardItem *item = new QStandardItem(value);

                item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                collegeModel->setItem(row, i, item);
            }
            row++;
        }
        file.close();
    }
    collegeModel->setHorizontalHeaderLabels({"College Name", "College Code"});
}


void MainWindow::on_tabWidget_currentChanged()
{

}


void MainWindow::on_Search_clicked() //search
{

}

void MainWindow::sortStudents(int index)
{
    int column = ui->Sort->currentData().toInt(); // Get column from combo box
    studentProxyModel->sort(column, Qt::AscendingOrder);
}

void MainWindow::on_Add_clicked()
{
    // Retrieve input values from the UI fields
    QString idNumber = ui->IDline->text();
    QString lastName = ui->Lastnameline->text();
    QString firstName = ui->Firstnameline->text();
    QString middleName = ui->Middlenameline->text();
    QString gender = ui->Genderline->currentText();
    QString yearLevel = ui->Yearlevelline->currentText();
    QString CourseCode = ui->CourseComboBox->currentText();

    // Ensure that all required fields are filled
    if (idNumber.isEmpty() || lastName.isEmpty() || firstName.isEmpty() || gender.isEmpty() || yearLevel.isEmpty() || CourseCode.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    // Create new row data
    QList<QStandardItem *> row;
    row.append(new QStandardItem(idNumber));
    row.append(new QStandardItem(lastName));
    row.append(new QStandardItem(firstName));
    row.append(new QStandardItem(middleName));
    row.append(new QStandardItem(gender));
    row.append(new QStandardItem(yearLevel));

    // Add new row to the model
    studentModel->appendRow(row);

    // Clear input fields after adding the data
    ui->IDline->clear();
    ui->Lastnameline->clear();
    ui->Firstnameline->clear();
    ui->Middlenameline->clear();
    ui->Gender->clear();
    ui->Yearlevelline->setCurrentIndex(0);

    QMessageBox::information(this, "Success", "Student added successfully!");
}


