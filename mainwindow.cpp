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

    loadCSVStudents("C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Student.csv");
    loadCSVProgram("C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV/Program.csv");
    loadCSVCollege("C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//College.csv");

    ui->StudentTable->setModel(studentModel);
    //ui->StudentTable->resizeColumnsToContents();
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

    ui->StudentTable->setSortingEnabled(true);
    ui->ProgTable->setSortingEnabled(true);

    // Enable column headers sorting directly
    ui->StudentTable->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder); // Default sorting by the first column
    ui->ProgTable->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
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
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "File Error", "Unable to open the CSV file.");
        return;
    }

    QTextStream in(&file);

    if (!in.atEnd())
        in.readLine();  // Skip the header row

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.isEmpty())
            continue;  // Ignore empty lines

        QStringList rowData = line.split(',');

        // Ensure exactly 7 columns
        while (rowData.size() < 7)
            rowData.append("");

        QList<QStandardItem *> items;
        for (const QString &value : rowData)
        {
            QStandardItem *item = new QStandardItem(value.trimmed());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            items.append(item);
        }

        studentModel->appendRow(items);
    }

    file.close();  // Close after reading

    studentModel->setHorizontalHeaderLabels({"I.D. Number", "Last Name", "First Name", "Middle Name", "Year Level", "Gender", "Course Code"});
}



void MainWindow::loadCSVProgram(const QString &filePath)
{
    programModel->clear();
    ui->CourseComboBox->clear();
    currentCSVProgram = filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        int row = 0;

        if (!in.atEnd()) // Skip the first line (header)
            in.readLine();

        while (!in.atEnd())
        {
            QString value = in.readLine().trimmed(); // Trim any extra spaces or newlines

            if (value.isEmpty()) // Ignore empty lines
                continue;

            QStringList rLine = value.split(',');

            if (rLine.size() > 1) // Assuming the first column contains course name
            {
                ui->CourseComboBox->addItem(rLine.at(0)); // Add course to ComboBox
            }

            programModel->appendRow({});

            for (int i = 0; i < rLine.size(); i++)
            {
                QStandardItem *item = new QStandardItem(rLine.at(i).trimmed());
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
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        int row = 0;

        QStringList allLines;
        while (!in.atEnd())
        {
            QString value = in.readLine().trimmed();
            if (!value.isEmpty())
                allLines.append(value);
        }

        // Skip the first line (header)
        if (!allLines.isEmpty())
        {
            allLines.removeFirst();
        }

        for (const QString &line : allLines)
        {
            QStringList rLine = line.split(',');

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


void MainWindow::on_AddStudent_clicked()
{
    // Validate required fields
    if (ui->Lastnameline->text().trimmed().isEmpty() ||
        ui->Firstnameline->text().trimmed().isEmpty() ||
        ui->IDline->text().trimmed().isEmpty() ||
        ui->Yearlevelline->currentText().toInt() == 0)
    {
        QMessageBox::critical(this, "Validation Error", "Please fill out all required fields (Last Name, First Name, ID, Year Level).");
        return;
    }

    // Extract values
    QString Las = ui->Lastnameline->text().trimmed();
    QString Fir = ui->Firstnameline->text().trimmed();
    QString Mid = ui->Middlenameline->text().trimmed(); // Middle name can be empty
    QString ID = ui->IDline->text().trimmed();
    QString Gen = ui->Genderline->currentText();
    int year = ui->Yearlevelline->currentText().toInt();
    QString Cou = ui->CourseComboBox->currentText();

    // Validate ID format (YYYY-NNNN)
    static const QRegularExpression idRegex(R"(^\d{4}-\d{4}$)");
    if (!idRegex.match(ID).hasMatch())
    {
        QMessageBox::critical(this, "ID Format Error", "Please enter the correct ID number format (YYYY-NNNN).");
        return;
    }

    const QString studentsFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Student.csv";

    QFile studentsFile(studentsFilePath);
    if (!studentsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Unable to open the students CSV file.");
        return;
    }

    QTextStream in(&studentsFile);
    QStringList csvData;
    bool idExists = false;  // Set to false initially

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(',');

        if (!parts.isEmpty() && parts[0].trimmed() == ID) // ID is in column 0
        {
            idExists = true;
            break;
        }
        csvData.append(line);
    }
    studentsFile.close();

    if (idExists)
    {
        QMessageBox::critical(this, "Duplicate ID Error", "The specified ID number already exists.");
        return;
    }

    // Format new student data correctly
    QString newData = ID + "," + Las + "," + Fir + "," + Mid + "," + QString::number(year) + "," + Gen + "," + Cou;

    // Open file in append mode
    if (!studentsFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::critical(this, "Error", "Unable to open the students CSV file for writing.");
        return;
    }

    QTextStream out(&studentsFile);
    out << newData << "\n";  // Append only new data
    studentsFile.close();

    loadCSVStudents(studentsFilePath);

    ui->StudentTable->setModel(studentModel);
    ui->StudentTable->resizeColumnsToContents();

    QMessageBox::information(this, "Success", "Student added successfully!");

    // Clear input fields
    ui->Lastnameline->clear();
    ui->Firstnameline->clear();
    ui->Middlenameline->clear();
    ui->IDline->clear();
    ui->Genderline->setCurrentIndex(0);
    ui->Yearlevelline->setCurrentIndex(0);
    ui->CourseComboBox->setCurrentIndex(0);
}

void MainWindow::on_EditStudent_clicked()
{

}

void MainWindow::on_tabWidget_currentChanged()
{

}


void MainWindow::on_Search_clicked() //search
{

}
void MainWindow::on_Edit_clicked() //search
{

}





