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
#include <QCompleter>


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
    ui->ProgTable->setModel(programModel);
    ui->CollegeTable->setModel(collegeModel);

    ui->ProgTable->resizeColumnsToContents();
    ui->CollegeTable->resizeColumnsToContents();

    ui -> CourseComboBox -> setCurrentIndex(-1);
    ui -> Genderline -> setCurrentIndex(-1);
    ui -> Yearlevelline -> setCurrentIndex(-1);
    ui -> CollegeCodeCombbox -> setCurrentIndex(-1);

    studentModel->setHorizontalHeaderLabels({"I.D. Number", "Last Name", "First Name", "Middle Name", "Year Level", "Gender", "Course Code"});
    programModel->setHorizontalHeaderLabels({"Program", "Program Name", "College Code"});
    collegeModel->setHorizontalHeaderLabels({"College Name", "College Code"});

    studentProxyModel->setSourceModel(studentModel);
    studentProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    studentProxyModel->setSortRole(Qt::DisplayRole);

    ui->StudentTable->setSortingEnabled(true);
    ui->ProgTable->setSortingEnabled(true);
    ui->CollegeTable->setSortingEnabled(true);

    // Enable column headers sorting directly
    ui->StudentTable->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    ui->ProgTable->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    ui->CollegeTable->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
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

    file.close();

    studentModel->setHorizontalHeaderLabels({"I.D. Number", "Last Name", "First Name", "Middle Name", "Year Level", "Gender", "Course Code"});
}

void MainWindow::loadCSVProgram(const QString &filePath)
{
    programModel->clear();
    ui->CourseComboBox->clear();
    currentCSVProgram = filePath;

    QFile file(filePath);
    QStringList courseList;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        int row = 0;

        if (!in.atEnd()) // Skip the first line (header)
            in.readLine();

        while (!in.atEnd())
        {
            QString value = in.readLine().trimmed();
            if (value.isEmpty()) continue;

            QStringList rLine = value.split(',');

            if (rLine.size() >= 3)  // Ensure at least Program Code, Program Name, and College Code are present
            {
                QString programCode = rLine.at(0).trimmed();   // Program Code
                QString programName = rLine.at(1).trimmed();   // Program Name
                QString collegeCode = rLine.at(2).trimmed();   // College Code

                // Add course (program code) to the ComboBox
                ui->CourseComboBox->addItem(programCode);
                courseList << programCode;
                // Append row data to the programModel
                QList<QStandardItem *> items;
                items << new QStandardItem(programCode)
                      << new QStandardItem(programName)
                      << new QStandardItem(collegeCode);

                // Make all items in the row non-editable
                for (auto &item : items)
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                programModel->appendRow(items);
                row++;
            }
        }
        file.close();
    }

    programModel->setHorizontalHeaderLabels({"Program", "Program Name", "College Code"});

    // Set up ComboBox with QCompleter for searchable dropdown
    ui->CourseComboBox->setEditable(true);  // Make ComboBox searchable
    QCompleter *completer = new QCompleter(courseList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);  // Match anywhere in the text
    ui->CourseComboBox->setCompleter(completer);
}

void MainWindow::loadCSVCollege(const QString &filePath)
{
    collegeModel->clear();
    ui->CollegeCodeCombbox->clear();
    currentCSVCollege = filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        int row = 0;

        if (!in.atEnd()) // Skip the first line (header)
            in.readLine();

        while (!in.atEnd())  // Read until the end of the file
        {
            QString value = in.readLine().trimmed();

            if (value.isEmpty())  // Ignore empty lines
                continue;

            QStringList rLine = value.split(',');

            if (rLine.size() > 1)  // first column contains college code and second contains college name
            {
                ui->CollegeCodeCombbox->addItem(rLine.at(0));  // Add college code to combo box (index 0)
            }

            collegeModel->appendRow({}); // Populate the collegeModel with the data

            for (int i = 0; i < rLine.size(); i++)
            {
                QString value = rLine.at(i);
                QStandardItem *item = new QStandardItem(value);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);  // Make the item non-editable
                collegeModel->setItem(row, i, item);
            }
            row++;  // Increment the row counter
        }

        file.close();
    }

    collegeModel->setHorizontalHeaderLabels({"College Code", "College Name"});
}

//Add Student funtion

void MainWindow::on_AddStudent_clicked()
{
    if (ui->Lastnameline->text().trimmed().isEmpty() ||
        ui->Firstnameline->text().trimmed().isEmpty() ||
        ui->IDline->text().trimmed().isEmpty() ||
        ui->Yearlevelline->currentText().toInt() == 0)
    {
        QMessageBox::critical(this, "Validation Error", "Please fill out all required fields (Last Name, First Name, ID, Year Level).");
        return;
    }

    QString Las = ui->Lastnameline->text().trimmed();
    QString Fir = ui->Firstnameline->text().trimmed();
    QString Mid = ui->Middlenameline->text().trimmed(); // Middle name can be empty
    QString ID = ui->IDline->text().trimmed();
    QString Gen = ui->Genderline->currentText();
    int year = ui->Yearlevelline->currentText().toInt();
    QString Cou = ui->CourseComboBox->currentText().trimmed();

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
    bool idExists = false;

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

    QString newStudentData = ID + "," + Las + "," + Fir + "," + Mid + "," + QString::number(year) + "," + Gen + "," + Cou;

    if (!studentsFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::critical(this, "Error", "Unable to open the students CSV file for writing.");
        return;
    }

    QTextStream out(&studentsFile);
    out << newStudentData << "\n";  // Append only new data
    studentsFile.close();

    loadCSVStudents(studentsFilePath);

    ui->StudentTable->setModel(studentModel);
    ui->StudentTable->resizeColumnsToContents();

    QMessageBox::information(this, "Success", "Student added successfully!");

    clearStudentInputFields();

}

void MainWindow::on_EditStudent_clicked() {
    QModelIndex currentIndex = ui->StudentTable->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a student to edit.");
        return;
    }

    int row = currentIndex.row();
    ui->IDline->setText(studentModel->item(row, 0)->text());
    ui->IDline->setReadOnly(true);
    ui->Lastnameline->setText(studentModel->item(row, 1)->text());
    ui->Firstnameline->setText(studentModel->item(row, 2)->text());
    ui->Middlenameline->setText(studentModel->item(row, 3)->text());
    ui->Yearlevelline->setCurrentText(studentModel->item(row, 4)->text());
    ui->Genderline->setCurrentText(studentModel->item(row, 5)->text());
    ui->CourseComboBox->setCurrentText(studentModel->item(row, 6)->text());

    isEditing = true;
    currentEditingRow = row;
}


void MainWindow::on_SaveStudent_clicked()
{
    if (!isEditing) {
        QMessageBox::warning(this, "No Edit", "Please select a student to edit first.");
        return;
    }
    // Get the updated values from the input fields
    QString updatedID = ui->IDline->text().trimmed();
    QString updatedLastName = ui->Lastnameline->text().trimmed();
    QString updatedFirstName = ui->Firstnameline->text().trimmed();
    QString updatedMiddleName = ui->Middlenameline->text().trimmed();
    QString updatedYearLevel = ui->Yearlevelline->currentText().trimmed();
    QString updatedGender = ui->Genderline->currentText().trimmed();
    QString updatedCourse = ui->CourseComboBox->currentText().trimmed();

    // Validate input
    if (updatedID.isEmpty() || updatedLastName.isEmpty() || updatedFirstName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all required fields.");
        return;
    }
    // Update the model with new data
    studentModel->setItem(currentEditingRow, 0, new QStandardItem(updatedID));
    studentModel->setItem(currentEditingRow, 1, new QStandardItem(updatedLastName));
    studentModel->setItem(currentEditingRow, 2, new QStandardItem(updatedFirstName));
    studentModel->setItem(currentEditingRow, 3, new QStandardItem(updatedMiddleName));
    studentModel->setItem(currentEditingRow, 4, new QStandardItem(updatedYearLevel));
    studentModel->setItem(currentEditingRow, 5, new QStandardItem(updatedGender));
    studentModel->setItem(currentEditingRow, 6, new QStandardItem(updatedCourse));

    updateStudentCSV();
    QMessageBox::information(this, "Success", "Student information updated successfully.");

    isEditing = false;
    currentEditingRow = -1;
    clearStudentInputFields();
}

void MainWindow::updateStudentCSV()
{
    QFile file(currentCSVStudent);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save student data.");
        return;
    }

    QTextStream out(&file);
    for (int row = 0; row < studentModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < studentModel->columnCount(); ++col) {
            rowData.append(studentModel->item(row, col)->text());
        }
        out << rowData.join(",") << "\n";
    }

    file.close();
}

void MainWindow::on_DeleteStudent_clicked()
{
    QModelIndex currentIndex = ui->StudentTable->currentIndex(); // Get selected student row
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a student to delete.");
        return;
    }

    int row = currentIndex.row();
    QString studentID = ui->StudentTable->model()->index(row, 0).data().toString().trimmed(); // Assuming student ID is in column 0

    if (studentID.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Student ID not found for the selected row.");
        return;
    }

    if (QMessageBox::question(this, "Confirm Deletion",
        QString("Are you sure you want to delete the student with ID '%1'?").arg(studentID),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    const QString studentFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Student.csv";

    // Delete student from Student.csv
    QFile studentFile(studentFilePath);
    if (!studentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the student file.");
        return;
    }

    QStringList updatedStudentData;
    QTextStream studentIn(&studentFile);
    while (!studentIn.atEnd()) {
        QString line = studentIn.readLine();
        QStringList parts = line.split(',');

        if (!parts.isEmpty() && parts[0].trimmed() != studentID) {
            updatedStudentData.append(line);
        }
    }
    studentFile.close();

    if (!studentFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Unable to write to the student file.");
        return;
    }

    QTextStream studentOut(&studentFile);
    for (const QString &line : updatedStudentData)
        studentOut << line << "\n";
    studentFile.close();

    loadCSVStudents(studentFilePath);
    QMessageBox::information(this, "Success", "Student deleted successfully.");
    clearStudentInputFields();
}

//Add program
void MainWindow::on_AddProgram_2_clicked()
{
    if (ui->ProgramCode_2->text().trimmed().isEmpty() ||
        ui->ProgramName_2->text().trimmed().isEmpty() ||
        ui->CollegeCodeCombbox->currentIndex() == -1)  // College Code must be selected
    {
        QMessageBox::critical(this, "Validation Error", "Please fill out all required fields (Program Code, Program Name, College Code).");
        return;
    }
    QString programCode = ui->ProgramCode_2->text().trimmed();
    QString programName = ui->ProgramName_2->text().trimmed();
    QString collegeCode = ui->CollegeCodeCombbox->currentText().trimmed();

    // Validate Program Code format (alphanumeric)
    static const QRegularExpression codeRegex(R"(^[A-Za-z0-9]+$)");
    if (!codeRegex.match(programCode).hasMatch())
    {
        QMessageBox::critical(this, "Program Code Format Error", "Please enter a valid Program Code (alphanumeric only).");
        return;
    }
    const QString programFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Program.csv";
    QFile programFile(programFilePath);

    if (!programFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Unable to open the program file.");
        return;
    }
    QTextStream programIn(&programFile);
    bool programCodeExists = false;

    while (!programIn.atEnd())
    {
        QString line = programIn.readLine();
        QStringList parts = line.split(',');

        if (!parts.isEmpty() && parts[0].trimmed() == programCode)
        {
            programCodeExists = true;
            break;
        }
    }
    programFile.close();

    if (programCodeExists)
    {
        QMessageBox::critical(this, "Duplicate Program Code Error", "The specified Program Code already exists.");
        return;
    }

    QString newProgramData = programCode + "," + programName + "," + collegeCode;

    if (!programFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::critical(this, "Error", "Unable to open the program file for writing.");
        return;
    }

    QTextStream out(&programFile);
    out << newProgramData << "\n";  // Append only new data
    programFile.close();

    loadCSVProgram(programFilePath);

    ui->ProgTable->setModel(programModel);
    ui->ProgTable->resizeColumnsToContents();


    QMessageBox::information(this, "Success", "Program added successfully!");

    clearStudentInputFields();
}

void MainWindow::on_EditProg_clicked() {
    QModelIndex selectIndex = ui->ProgTable->currentIndex();

    if (!selectIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a Program to edit.");
        return;
    }

    QString oldProgramCode = ui->ProgTable->model()->data(ui->ProgTable->model()->index(selectIndex.row(), 0)).toString().trimmed();
    ui->ProgramCode_2->setText(oldProgramCode);
    ui->ProgramName_2->setText(ui->ProgTable->model()->data(ui->ProgTable->model()->index(selectIndex.row(), 1)).toString());
    ui->CollegeCodeCombbox->setCurrentText(ui->ProgTable->model()->data(ui->ProgTable->model()->index(selectIndex.row(), 2)).toString());

    isEditing = true;
    currentEditingRow = selectIndex.row();
}

void MainWindow::on_SaveProg_clicked() {
    if (!isEditing) {
        QMessageBox::warning(this, "No Edit", "Please select a program to edit first.");
        return;
    }
    QString updatedProgramCode = ui->ProgramCode_2->text().trimmed();
    QString updatedProgramName = ui->ProgramName_2->text().trimmed();
    QString updatedCollegeCode = ui->CollegeCodeCombbox->currentText().trimmed();

    if (updatedProgramCode.isEmpty() || updatedProgramName.isEmpty() || updatedCollegeCode.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all required fields.");
        return;
    }

    QString oldProgramCode = programModel->item(currentEditingRow, 0)->text().trimmed();

    programModel->setItem(currentEditingRow, 0, new QStandardItem(updatedProgramCode));
    programModel->setItem(currentEditingRow, 1, new QStandardItem(updatedProgramName));
    programModel->setItem(currentEditingRow, 2, new QStandardItem(updatedCollegeCode));

    updateProgramCSV();

    // Update student CSV with the new program code if it matches the old program code
    for (int row = 0; row < studentModel->rowCount(); ++row) {
        if (studentModel->item(row, 6)->text().trimmed() == oldProgramCode) {
            studentModel->setItem(row, 6, new QStandardItem(updatedProgramCode));
        }
    }
    updateStudentCSV();

    QMessageBox::information(this, "Success", "Program and related student records updated successfully.");

    isEditing = false;
    currentEditingRow = -1;
    clearProgramInputFields();
}

void MainWindow::on_DeleteProgram_clicked()
{
    QModelIndex currentIndex = ui->ProgTable->currentIndex(); // Get selected program row
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a program to delete.");
        return;
    }

    int row = currentIndex.row();
    QString selectedProgramCode = ui->ProgTable->model()->index(row, 0).data().toString().trimmed(); // Program code in column 0

    if (selectedProgramCode.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Program code not found for the selected row.");
        return;
    }

    if (QMessageBox::question(this, "Confirm Deletion",
        QString("Are you sure you want to delete the program '%1'? All related students will be updated to 'Unenrolled'.").arg(selectedProgramCode),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    const QString programFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Program.csv";
    const QString studentFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Student.csv";

    // Delete the program from Program.csv
    QFile programFile(programFilePath);
    if (!programFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the program file.");
        return;
    }

    QStringList updatedProgramData;
    QTextStream programIn(&programFile);
    while (!programIn.atEnd()) {
        QString line = programIn.readLine();
        QStringList parts = line.split(',');

        if (!parts.isEmpty() && parts[0].trimmed() != selectedProgramCode) {
            updatedProgramData.append(line);
        }
    }
    programFile.close();

    if (!programFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Unable to write to the program file.");
        return;
    }

    QTextStream programOut(&programFile);
    for (const QString &line : updatedProgramData)
        programOut << line << "\n";
    programFile.close();
    loadCSVProgram(programFilePath); // Refresh program data

    //Update students under the deleted program to "Unenrolled"
    QFile studentFile(studentFilePath);
    if (!studentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the student file.");
        return;
    }

    QStringList updatedStudentData;
    QTextStream studentIn(&studentFile);
    while (!studentIn.atEnd()) {
        QString line = studentIn.readLine();
        QStringList parts = line.split(',');

        // Update course to "Unenrolled" if it matches the deleted program
        if (parts.size() >= 7 && parts[6].trimmed() == selectedProgramCode) {
            parts[6] = "Unenrolled";
            line = parts.join(",");
        }
        updatedStudentData.append(line);
    }
    studentFile.close();

    if (!studentFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Unable to write to the student file.");
        return;
    }

    QTextStream studentOut(&studentFile);
    for (const QString &line : updatedStudentData)
        studentOut << line << "\n";
    studentFile.close();
    loadCSVStudents(studentFilePath); // Refresh student data

    QMessageBox::information(this, "Success", "Program deleted and related students updated to 'Unenrolled' successfully.");
    clearProgramInputFields();
}

void MainWindow::updateProgramCSV()
{
    const QString programFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Program.csv";
    QFile programFile(programFilePath);

    if (!programFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the program file for saving.");
        return;
    }

    QTextStream out(&programFile);

    for (int row = 0; row < programModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < programModel->columnCount(); ++col) {
            rowData.append(programModel->item(row, col)->text());
        }
        out << rowData.join(",") << "\n";
    }

    programFile.close();
}


//Add College

void MainWindow::on_AddCollege_2_clicked() {

    if (ui->CollegeCodeLine->text().trimmed().isEmpty() ||
        ui->CollegeNameLine->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, "Validation Error", "Please fill out all required fields (College Code, College Name).");
        return;
    }

    QString collegeCode = ui->CollegeCodeLine->text().trimmed();
    QString collegeName = ui->CollegeNameLine->text().trimmed();

    static const QRegularExpression codeRegex(R"(^[A-Za-z0-9]+$)");
    if (!codeRegex.match(collegeCode).hasMatch()) {
        QMessageBox::critical(this, "College Code Format Error", "Please enter a valid College Code (alphanumeric only).");
        return;
    }

    const QString collegeFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//College.csv";

    QFile collegeFile(collegeFilePath);

    if (!collegeFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the college file.");
        return;
    }

    QTextStream in(&collegeFile);
    QStringList csvData;
    bool codeExists = false;

    // Check if the college code already exists
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');

        if (!parts.isEmpty() && parts[0].trimmed() == collegeCode) { // Check by college code (college code comes first now)
            codeExists = true;
            break;
        }
        csvData.append(line);
    }

    // If code exists, show error
    if (codeExists) {
        QMessageBox::critical(this, "Duplicate Code Error", "The specified College Code already exists.");
        return;
    }

    QString newCollegeData = collegeCode + "," + collegeName;

    collegeFile.seek(collegeFile.size()); // Move the cursor to the end of the file for appending
    QTextStream out(&collegeFile);
    out << newCollegeData << "\n";  // Append new college data
    collegeFile.close();

    loadCSVCollege(collegeFilePath);

    QMessageBox::information(this, "Success", "College added successfully!");
    clearStudentInputFields();
}

void MainWindow::on_EditCollege_clicked() {
    QModelIndex selectedIndex = ui->CollegeTable->currentIndex();

    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a college to edit.");
        return;
    }
    QString oldCollegeCode = ui->CollegeTable->model()->data(ui->CollegeTable->model()->index(selectedIndex.row(), 0)).toString().trimmed();

    ui->CollegeCodeLine->setText(oldCollegeCode);
    ui->CollegeNameLine->setText(ui->CollegeTable->model()->data(ui->CollegeTable->model()->index(selectedIndex.row(), 1)).toString());

    isEditing = true;
    currentEditingRow = selectedIndex.row();
}

void MainWindow::on_SaveCollege_clicked() {
    if (!isEditing) {
        QMessageBox::warning(this, "No Edit", "Please select a college to edit first.");
        return;
    }
    QString updatedCollegeCode = ui->CollegeCodeLine->text().trimmed();    // Get updated values from input fields
    QString updatedCollegeName = ui->CollegeNameLine->text().trimmed();

    if (updatedCollegeCode.isEmpty() || updatedCollegeName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "College code and name cannot be empty.");
        return;
    }
    QString oldCollegeCode = collegeModel->item(currentEditingRow, 0)->text().trimmed();
    // Update college data in the model
    collegeModel->setItem(currentEditingRow, 0, new QStandardItem(updatedCollegeCode));
    collegeModel->setItem(currentEditingRow, 1, new QStandardItem(updatedCollegeName));

    updateCollegeCSV();

    // Update related program college codes if they match the old college code
    for (int row = 0; row < programModel->rowCount(); ++row) {
        if (programModel->item(row, 2)->text().trimmed() == oldCollegeCode) {
            programModel->setItem(row, 2, new QStandardItem(updatedCollegeCode));
        }
    }
    updateProgramCSV(); // Save updated program data

    QMessageBox::information(this, "Success", "College and related programs updated successfully.");

    isEditing = false;
    currentEditingRow = -1;
    clearCollegeInputFields();
}

void MainWindow::on_DeleteCollege_clicked()
{
    QModelIndex currentIndex = ui->CollegeTable->currentIndex(); // Get selected college row
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a college to delete.");
        return;
    }

    int row = currentIndex.row();
    QString selectedCollegeCode = ui->CollegeTable->model()->index(row, 0).data().toString().trimmed(); // College code in column 0

    if (selectedCollegeCode.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "College code not found for the selected row.");
        return;
    }

    if (QMessageBox::question(this, "Confirm Deletion",
        QString("Are you sure you want to delete the college '%1'? All related programs will be updated to 'N/A'.").arg(selectedCollegeCode),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    const QString collegeFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//College.csv";
    const QString programFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Program.csv";

    QFile collegeFile(collegeFilePath);
    if (!collegeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the college file.");
        return;
    }

    QStringList updatedCollegeData;
    QTextStream collegeIn(&collegeFile);
    while (!collegeIn.atEnd()) {
        QString line = collegeIn.readLine();
        QStringList parts = line.split(',');

        if (!parts.isEmpty() && parts[0].trimmed() != selectedCollegeCode) {
            updatedCollegeData.append(line);
        }
    }
    collegeFile.close();

    if (!collegeFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Unable to write to the college file.");
        return;
    }

    QTextStream collegeOut(&collegeFile);
    for (const QString &line : updatedCollegeData)
        collegeOut << line << "\n";
    collegeFile.close();
    loadCSVCollege(collegeFilePath); // Refresh college data

    QFile programFile(programFilePath);
    if (!programFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the program file.");
        return;
    }

    QStringList updatedProgramData;
    QTextStream programIn(&programFile);
    while (!programIn.atEnd()) {
        QString line = programIn.readLine();
        QStringList parts = line.split(',');

        if (parts.size() >= 3 && parts[2].trimmed() == selectedCollegeCode) {
            parts[2] = "N/A";  // Set college code to N/A for matching programs
            line = parts.join(",");
        }
        updatedProgramData.append(line);
    }
    programFile.close();

    if (!programFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Unable to write to the program file.");
        return;
    }

    QTextStream programOut(&programFile);
    for (const QString &line : updatedProgramData)
        programOut << line << "\n";
    programFile.close();
    loadCSVProgram(programFilePath); // Refresh program data

    QMessageBox::information(this, "Success", "College deleted and related programs updated to 'N/A' successfully.");
    clearCollegeInputFields();
}

void MainWindow::updateCollegeCSV()
{
    const QString collegeFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//College.csv";
    QFile collegeFile(collegeFilePath);

    if (!collegeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the college file for saving.");
        return;
    }

    QTextStream out(&collegeFile);

    // Iterate over the rows in the model to collect the data
    for (int row = 0; row < collegeModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < collegeModel->columnCount(); ++col) {
            rowData.append(collegeModel->item(row, col)->text());
        }
        out << rowData.join(",") << "\n";
    }

    collegeFile.close();
}

//Search
void MainWindow::on_Search_clicked()
{
    QString searchTerm = ui->SearchLine->text().trimmed();

    if (searchTerm.isEmpty()) {
        loadCSVStudents("C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Student.csv");
        loadCSVProgram("C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Program.csv");
        loadCSVCollege("C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//College.csv");

        ui->StudentTable->setModel(studentModel);
        ui->StudentTable->resizeColumnsToContents();

        ui->ProgTable->setModel(programModel);
        ui->ProgTable->resizeColumnsToContents();

        ui->CollegeTable->setModel(collegeModel);
        ui->CollegeTable->resizeColumnsToContents();

        QMessageBox::information(this, "Search Reset", "All data has been reloaded.");
        return;
    }

    bool studentFound = false;
    bool programFound = false;
    bool collegeFound = false;

    // Search Student
    for (int row = 0; row < studentModel->rowCount(); ++row) {
        bool rowMatches = false;
        for (int col = 0; col < studentModel->columnCount(); ++col) {
            QString cellText = studentModel->item(row, col)->text();
            if (cellText.contains(searchTerm, Qt::CaseInsensitive)) {
                rowMatches = true;
                studentFound = true;
                break;
            }
        }
        ui->StudentTable->setRowHidden(row, !rowMatches);
    }

    // Search Program Table
    for (int row = 0; row < programModel->rowCount(); ++row) {
        bool rowMatches = false;
        for (int col = 0; col < programModel->columnCount(); ++col) {
            QString cellText = programModel->item(row, col)->text();
            if (cellText.contains(searchTerm, Qt::CaseInsensitive)) {
                rowMatches = true;
                programFound = true;
                break;
            }
        }
        ui->ProgTable->setRowHidden(row, !rowMatches);
    }

    // Search College Table
    for (int row = 0; row < collegeModel->rowCount(); ++row) {
        bool rowMatches = false;
        for (int col = 0; col < collegeModel->columnCount(); ++col) {
            QString cellText = collegeModel->item(row, col)->text();
            if (cellText.contains(searchTerm, Qt::CaseInsensitive)) {
                rowMatches = true;
                collegeFound = true;
                break;
            }
        }
        ui->CollegeTable->setRowHidden(row, !rowMatches);
    }

    if (!studentFound && !programFound && !collegeFound) {
        QMessageBox::information(this, "Search", "No matching records found in students, programs, or colleges.");
    }
}

void MainWindow::on_DeleteButton_clicked()
{
    int currentTab = ui->TabTable->currentIndex();
    QTableView *currentTable = nullptr;

    switch (currentTab) {
    case 0:
        currentTable = ui->StudentTable;
        break;
    case 1:
        currentTable = ui->ProgTable;
        break;
    case 2:
        currentTable = ui->CollegeTable;
        break;
    default:
        QMessageBox::warning(this, "Tab Error", "Unknown tab selected.");
        return;
    }

    QItemSelectionModel *selectionModel = currentTable->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select an item to delete.");
        return;
    }

    QSet<int> uniqueRows;
    for (const QModelIndex &index : selectedIndexes) {
        uniqueRows.insert(index.row());
    }

    if (uniqueRows.size() > 1) {
        QMessageBox::critical(this, "Selection Error", "Please select only one row to delete.");
        return;
    }

    switch (currentTab) {
    case 0:
        on_DeleteStudent_clicked();
        break;
    case 1:
        on_DeleteProgram_clicked();
        break;
    case 2:
        on_DeleteCollege_clicked();
        break;
    }
}


//Clear
void MainWindow::clearStudentInputFields()
{
    ui->IDline->clear();
    ui->IDline->setReadOnly(true);
    ui->Lastnameline->clear();
    ui->Firstnameline->clear();
    ui->Middlenameline->clear();
    ui->Yearlevelline->setCurrentIndex(-1);
    ui->Genderline->setCurrentIndex(-1);
    ui->CourseComboBox->setCurrentIndex(-1);

    isEditing = false;
    currentEditingRow = -1;
}

void MainWindow::clearProgramInputFields(){
    ui->ProgramCode_2->clear();
    ui->ProgramName_2->clear();
    ui->CollegeCodeCombbox->setCurrentIndex(-1);

    isEditing = false;
    currentEditingRow = -1;
}

void MainWindow::clearCollegeInputFields()
{
    ui->CollegeCodeLine->clear();
    ui->CollegeNameLine->clear();

    isEditing = false;
    currentEditingRow = -1;
}
























