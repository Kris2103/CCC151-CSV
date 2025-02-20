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

    studentModel->setHorizontalHeaderLabels({"I.D. Number", "Last Name", "First Name", "Middle Name", "Year Level", "Gender", "Course Code"});
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

    file.close();

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
    collegeModel->clear();  // Clear any existing data in the model
    ui->CollegeCodeCombbox->clear();  // Clear the combo box
    currentCSVCollege = filePath;  // Store the current CSV file path

    QFile file(filePath);  // Open the file
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);  // Read the file content
        int row = 0;

        if (!in.atEnd()) // Skip the first line (header)
            in.readLine();

        while (!in.atEnd())  // Read until the end of the file
        {
            QString value = in.readLine().trimmed();  // Read and trim each line

            if (value.isEmpty())  // Ignore empty lines
                continue;

            QStringList rLine = value.split(',');  // Split the line into columns

            if (rLine.size() > 1)  // Assuming the first column contains college code and second contains college name
            {
                // Populate the CollegeCodeCombbox with college codes
                ui->CollegeCodeCombbox->addItem(rLine.at(0));  // Add college code to combo box (index 0)
            }

            // Populate the collegeModel with the data (for displaying in a table or list)
            collegeModel->appendRow({});

            for (int i = 0; i < rLine.size(); i++)
            {
                QString value = rLine.at(i);
                QStandardItem *item = new QStandardItem(value);  // Create a new item for each column
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);  // Make the item non-editable
                collegeModel->setItem(row, i, item);  // Set the item in the model
            }
            row++;  // Increment the row counter
        }

        file.close();  // Close the file after reading
    }

    // Set the horizontal headers for the college model (College Code first, then College Name)
    collegeModel->setHorizontalHeaderLabels({"College Code", "College Name"});
}

//Add Student funtion

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
    QString newStudentData = ID + "," + Las + "," + Fir + "," + Mid + "," + QString::number(year) + "," + Gen + "," + Cou;

    // Open file in append mode
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

    // Clear input fields
    ui->Lastnameline->clear();
    ui->Firstnameline->clear();
    ui->Middlenameline->clear();
    ui->IDline->clear();
    ui->Genderline->setCurrentIndex(-1);
    ui->Yearlevelline->setCurrentIndex(-1);
    ui->CourseComboBox->setCurrentIndex(-1);
}

void MainWindow::on_EditStudent_clicked()
{
    QModelIndex currentIndex = ui->StudentTable->currentIndex(); // Get selected row

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a student to edit.");
        return;
    }

    int row = currentIndex.row(); // Get the row index of the selected student

    // Retrieve data from the selected row
    QString ID = studentModel->item(row, 0)->text();
    QString lastName = studentModel->item(row, 1)->text();
    QString firstName = studentModel->item(row, 2)->text();
    QString middleName = studentModel->item(row, 3)->text();
    QString yearLevel = studentModel->item(row, 4)->text();
    QString gender = studentModel->item(row, 5)->text();
    QString course = studentModel->item(row, 6)->text();

    // Populate the input fields for editing
    ui->IDline->setText(ID);
    ui->Lastnameline->setText(lastName);
    ui->Firstnameline->setText(firstName);
    ui->Middlenameline->setText(middleName);
    ui->Yearlevelline->setCurrentText(yearLevel);
    ui->Genderline->setCurrentText(gender);
    ui->CourseComboBox->setCurrentText(course);

    // Set a flag to indicate that the user is in edit mode
    isEditing = true;
    currentEditingRow = row;
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

    // Step: Delete student from Student.csv
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

    // Update the CSV file with the new data
    updateStudentCSV();

    // Notify user of success
    QMessageBox::information(this, "Success", "Student information updated successfully.");

    // Reset editing state
    isEditing = false;
    currentEditingRow = -1;  // Reset to no editing row
}

void MainWindow::updateStudentCSV()
{
    qDebug() << "Updating CSV file...";

    QFile file(currentCSVStudent);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save student data.");
        return;
    }

    QTextStream out(&file);

    // Write headers (optional)
    out << "ID,Last Name,First Name,Middle Name,Year Level,Gender,Course\n";

    for (int row = 0; row < studentModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < studentModel->columnCount(); ++col) {
            rowData.append(studentModel->item(row, col)->text());
        }
        out << rowData.join(",") << "\n";
    }

    file.close();
    qDebug() << "CSV update complete.";
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

    ui->CollegeCodeLine->clear();
    ui->CollegeNameLine->clear();
}

void MainWindow::on_EditCollege_clicked()
{
    QModelIndex selectedIndex = ui->CollegeTable->currentIndex();  // Assuming CollegeTable is your table for displaying colleges.

    // Ensure a row is selected
    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a college to edit.");
        return;
    }

    // Get the college code and name from the selected row
    QString collegeCode = ui->CollegeTable->model()->data(ui->CollegeTable->model()->index(selectedIndex.row(), 0)).toString();
    QString collegeName = ui->CollegeTable->model()->data(ui->CollegeTable->model()->index(selectedIndex.row(), 1)).toString();

    // Set the data in the input fields
    ui->CollegeCodeLine->setText(collegeCode);
    ui->CollegeNameLine->setText(collegeName);

    // Set a flag to indicate that you are editing
    isEditing = true;
    currentEditingRow = selectedIndex.row();  // Store the index of the selected row
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

    // Step 1: Delete the program from Program.csv
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

        // Keep all programs except the one being deleted
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

    // Step 2: Update students under the deleted program to "Unenrolled"
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
}

void MainWindow::on_SaveCollege_clicked()
{
    if (!isEditing) {
        QMessageBox::warning(this, "No Edit", "Please select a college to edit first.");
        return;
    }

    // Get the updated values from the input fields
    QString updatedCollegeCode = ui->CollegeCodeLine->text().trimmed();
    QString updatedCollegeName = ui->CollegeNameLine->text().trimmed();

    // Validate the input
    if (updatedCollegeCode.isEmpty() || updatedCollegeName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all required fields.");
        return;
    }

    // Update the model with new data
    collegeModel->setItem(currentEditingRow, 0, new QStandardItem(updatedCollegeCode));
    collegeModel->setItem(currentEditingRow, 1, new QStandardItem(updatedCollegeName));

    // Update the CSV file with the new data
    updateCollegeCSV();

    // Notify user of success
    QMessageBox::information(this, "Success", "College information updated successfully.");

    // Reset editing state
    isEditing = false;
    currentEditingRow = -1;  // Reset to no editing row
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
    qDebug() << "College CSV update complete.";
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

    ui->ProgramCode_2->clear();
    ui->ProgramName_2->clear();
    ui->CollegeCodeCombbox->setCurrentIndex(-1);

}

void MainWindow::on_EditProg_clicked()
{
    QModelIndex currentIndex = ui->ProgTable->currentIndex(); // Get selected row

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a Program to edit.");
        return;
    }

    int row = currentIndex.row(); // Get the row index of the selected student

    QString programCode = programModel->item(row, 0)->text();
    QString programName = programModel->item(row, 1)->text();
    QString collegeCode = programModel->item(row, 2)->text();

    ui->ProgramCode_2->setText(programCode);
    ui->ProgramName_2->setText(programName);
    ui->CollegeCodeCombbox->setCurrentText(collegeCode);

    isEditing = true;
    currentEditingRow = row;

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
}

void MainWindow::on_SaveProg_clicked()
{
    if (!isEditing) {
    QMessageBox::warning(this, "No Edit", "Please select a program to edit first.");
    return;
    }

    // Get the updated values from the input fields
    QString updatedProgramCode = ui->ProgramCode_2->text().trimmed();
    QString updatedProgramName = ui->ProgramName_2->text().trimmed();

    // Validate the input
    if (updatedProgramCode.isEmpty() || updatedProgramName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all required fields.");
        return;
    }

    // Update the model with new data
    programModel->setItem(currentEditingRow, 0, new QStandardItem(updatedProgramCode));
    programModel->setItem(currentEditingRow, 1, new QStandardItem(updatedProgramName));

    // Update the CSV file with the new data
    updateProgramCSV();

    // Notify user of success
    QMessageBox::information(this, "Success", "Program information updated successfully.");

    // Reset editing state
    isEditing = false;
    currentEditingRow = -1;  // Reset to no editing row*/
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
    qDebug() << "Program CSV update complete.";
}


void MainWindow::on_Search_clicked()
{
    QString searchTerm = ui->SearchLine->text().trimmed(); // Assuming you have a QLineEdit named SearchLineEdit

    if (searchTerm.isEmpty()) {
        QMessageBox::information(this, "Search", "Please enter a search term.");
        return;
    }

    bool found = false;
    for (int row = 0; row < studentModel->rowCount(); ++row) {
        bool rowMatches = false;
        for (int col = 0; col < studentModel->columnCount(); ++col) {
            QString cellText = studentModel->item(row, col)->text();
            if (cellText.contains(searchTerm, Qt::CaseInsensitive)) {
                rowMatches = true;
                found = true;
                break;
            }
        }

        ui->StudentTable->setRowHidden(row, !rowMatches); // Hide non-matching rows
    }

    if (!found) {
        QMessageBox::information(this, "Search", "No matching records found.");
    }
}



void MainWindow::on_TabTable_currentChanged(int index){

}
void MainWindow::on_tabWidget_currentChanged()
{

}
















