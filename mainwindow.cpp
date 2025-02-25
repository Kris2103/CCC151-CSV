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

    ui->CollegeTable->setModel(collegeModel);
    collegeModel->setHorizontalHeaderLabels({"College Code", "College Name"});

    ui->CollegeTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);  // College Code
    ui->CollegeTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);           // College Name
    ui->CollegeTable->horizontalHeader()->setStretchLastSection(true);
    ui->CollegeTable->horizontalHeader()->setMinimumSectionSize(150);


    ui->ProgTable->setColumnWidth(0, 100);   // Program Code (fixed width)
    ui->ProgTable->setColumnWidth(2, 100);   // College Code (fixed width)

    ui->ProgTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);  // Program Name

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
    ui->CourseComboBox->setCurrentIndex(-1);
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
    ui->ProgTable->setModel(programModel);
    ui->ProgTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    // Fixed width for Program Code and College Code
    ui->ProgTable->setColumnWidth(0, 100);  // Program Code
    ui->ProgTable->setColumnWidth(2, 100);  // College Code

    // Middle column stretches dynamically
    ui->ProgTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
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
    ui->CollegeCodeCombbox->setCurrentIndex(-1);
    ui->CollegeCodeCombbox->clear();
    currentCSVCollege = filePath;

    QFile file(filePath);
    QStringList collegeList;

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

            if (rLine.size() > 1)  // first column: college code, second: college name
            {
                QString collegeCode = rLine.at(0).trimmed();
                ui->CollegeCodeCombbox->addItem(collegeCode);  // Add college code to ComboBox
                collegeList << collegeCode;
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
    ui->CollegeCodeCombbox->setEditable(true);  // Enable text input
    QCompleter *collegeCompleter = new QCompleter(collegeList, this);
    collegeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    collegeCompleter->setFilterMode(Qt::MatchContains);  // Match anywhere in text
    ui->CollegeCodeCombbox->setCompleter(collegeCompleter);
}

//Add Student funtion

void MainWindow::on_AddStudent_clicked()
{
    if (isEditing) {
        QMessageBox::warning(this, "Edit in Progress",
                             "You are currently editing a student. Please click 'Update' to save changes or clear the fields to cancel.");
        return;
    }

    if (ui->Lastnameline->text().trimmed().isEmpty() ||
        ui->Firstnameline->text().trimmed().isEmpty() ||
        ui->IDline->text().trimmed().isEmpty() ||
        ui->Yearlevelline->currentText().toInt() == 0 ||
        ui->CourseComboBox->currentText().trimmed().isEmpty() ||
        ui->Genderline->currentText().trimmed().isEmpty())
    {
        QMessageBox::critical(this, "Validation Error", "Please fill out all required fields (Last Name, First Name, ID, Year Level, Course code, Gender).");
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
    //
    const QString programFilePath = "C://Users//Kristelle//Documents//BSCS-3//CCC151 - Database Management//CCC151-CSV//Program.csv";
    QFile programFile(programFilePath);
    if (!programFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Unable to open the program CSV file.");
        return;
    }

    QTextStream programIn(&programFile);
    bool courseExists = false;
    while (!programIn.atEnd())
    {
        QString line = programIn.readLine();
        QStringList parts = line.split(',');

        if (!parts.isEmpty() && parts[0].trimmed() == Cou) // Assuming course code is in column 0
        {
            courseExists = true;
            break;
        }
    }
    programFile.close();

    if (!courseExists)
    {
        QMessageBox::critical(this, "Course Code Error", "The selected course code does not exist. Please select a valid course.");
        return;
    }

    //
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

    QMessageBox::information(this, "Success", "Student added successfully!");
    ui->IDline->clear();
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
    bool courseExists = false;
    for (int row = 0; row < programModel->rowCount(); ++row) {
        if (programModel->item(row, 0)->text().trimmed() == updatedCourse) {
            courseExists = true;
            break;
        }
    }

    if (!courseExists) {
        QMessageBox::critical(this, "Course Code Error",
                              QString("The course code '%1' does not exist. Please select a valid course code.").arg(updatedCourse));
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
    ui->IDline->clear();
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

    out << "ID,LastName,FirstName,MiddleName,YearLevel,Gender,ProgramCode\n";

    for (int row = 0; row < studentModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < studentModel->columnCount(); ++col) {
            QStandardItem *item = studentModel->item(row, col);
            QString cellText = item ? item->text() : "";

            if (cellText.contains(",")) {
                cellText = "\"" + cellText + "\"";
            }
            rowData.append(cellText);
        }
        out << rowData.join(",") << "\n";
    }

    out.flush();
    file.close();
}


void MainWindow::on_DeleteStudent_clicked()
{
    QModelIndex currentIndex = ui->StudentTable->currentIndex(); // Get selected student row
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a student to delete.");
        return;
    }

    QString studentID = ui->StudentTable->model()->index(currentIndex.row(), 0).data().toString().trimmed(); // Assuming ID is column 0

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

    QFile studentFile(studentFilePath);
    if (!studentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the student file.");
        return;
    }

    QTextStream studentIn(&studentFile);
    QString headerLine = studentIn.readLine();  // Always preserve header
    QStringList updatedStudentData;
    bool studentDeleted = false;

    while (!studentIn.atEnd()) {
        QString line = studentIn.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',');
        if (!parts.isEmpty() && parts[0].trimmed() == studentID) {
            studentDeleted = true;  // This is the student to delete, skip adding it
            continue;
        }
        updatedStudentData.append(line);
    }
    studentFile.close();

    if (!studentDeleted) {
        QMessageBox::warning(this, "Deletion Error", "Selected student not found.");
        return;
    }

    if (!studentFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Unable to write to the student file.");
        return;
    }

    QTextStream studentOut(&studentFile);
    studentOut << headerLine << "\n";  // Re-add header first
    for (int i = 0; i < updatedStudentData.size(); ++i) {
        studentOut << updatedStudentData[i];
        if (i != updatedStudentData.size() - 1) studentOut << "\n";
    }
    studentFile.close();

    loadCSVStudents(studentFilePath);    // Refresh table
    ui->StudentTable->clearSelection();  // Clear selection
    clearStudentInputFields();           // Reset fields

    QMessageBox::information(this, "Success", "Student deleted successfully.");
}



//Add program
void MainWindow::on_AddProgram_2_clicked()
{
    if (isEditing) {
        QMessageBox::warning(this, "Edit in Progress",
                             "You are currently editing a program. Please click 'Update' to save changes or clear the fields to cancel.");
        return;
    }
    if (ui->ProgramCode_2->text().trimmed().isEmpty() ||
        ui->ProgramName_2->text().trimmed().isEmpty() ||
        ui->CollegeCodeCombbox->currentText().trimmed().isEmpty())  // College Code must be selected
    {
        QMessageBox::critical(this, "Validation Error", "Please fill out all required fields (Program Code, Program Name, College Code).");
        return;
    }
    QString programCode = ui->ProgramCode_2->text().trimmed();
    QString programName = ui->ProgramName_2->text().trimmed();
    QString collegeCode = ui->CollegeCodeCombbox->currentText().trimmed();

    //
    if (ui->CollegeCodeCombbox->findText(collegeCode, Qt::MatchFixedString | Qt::MatchCaseSensitive) == -1)
    {
        QMessageBox::critical(this, "Invalid College Code", "The specified College Code does not exist. Please select a valid one.");
        return;
    }
    //

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

    QMessageBox::information(this, "Success", "Program added successfully!");

    clearProgramInputFields();
}

void MainWindow::on_EditProg_clicked() {
    QItemSelectionModel *selectionModel = ui->ProgTable->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select a Program to edit.");
        return;
    }

    QSet<int> uniqueRows;
    for (const QModelIndex &index : selectedIndexes) {
        uniqueRows.insert(index.row());
    }

    if (uniqueRows.size() > 1) {
        QMessageBox::critical(this, "Selection Error", "Please select only one row to edit.");
        return;
    }

    int selectedRow = *uniqueRows.begin();  // Get the single row index
    QString oldProgramCode = ui->ProgTable->model()->data(ui->ProgTable->model()->index(selectedRow, 0)).toString().trimmed();
    ui->ProgramCode_2->setText(oldProgramCode);
    ui->ProgramName_2->setText(ui->ProgTable->model()->data(ui->ProgTable->model()->index(selectedRow, 1)).toString());
    ui->CollegeCodeCombbox->setCurrentText(ui->ProgTable->model()->data(ui->ProgTable->model()->index(selectedRow, 2)).toString());

    isEditing = true;
    currentEditingRow = selectedRow;
    ui->SaveProg->setText("Update");
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
    //
    bool collegeExists = false;
    for (int row = 0; row < collegeModel->rowCount(); ++row) {
        if (collegeModel->item(row, 0)->text().trimmed() == updatedCollegeCode) {
            collegeExists = true;
            break;
        }
    }

    if (!collegeExists) {
        QMessageBox::critical(this, "College Code Error", "The specified college code does not exist. Please select a valid college code.");
        return;
    }
    //

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
    refreshCourseComboBox();
    ui->CourseComboBox->setCurrentIndex(-1);

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
    refreshCourseComboBox();
    refreshCollegeCodeComboBox();

    QMessageBox::information(this, "Success", "Program deleted and related students updated to 'Unenrolled' successfully.");
    ui->CollegeCodeCombbox->setCurrentIndex(-1);
    ui->CourseComboBox->setCurrentIndex(-1);
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

    out << "ProgramCode,ProgramName,CollegeCode\n";

    for (int row = 0; row < programModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < programModel->columnCount(); ++col) {
            QStandardItem *item = programModel->item(row, col);
            QString cellText = item ? item->text() : "";
            // ✅ Handle commas by wrapping text in quotes
            if (cellText.contains(",")) {
                cellText = "\"" + cellText + "\"";
            }
            rowData.append(cellText);
        }
        out << rowData.join(",") << "\n";
    }

    out.flush();
    programFile.close();
}

//Add College

void MainWindow::on_AddCollege_2_clicked() {

    if (isEditing) {
        QMessageBox::warning(this, "Edit in Progress",
                             "You are currently editing a college. Please click 'Update' to save changes or clear the fields to cancel.");
        return;
    }

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
    if (!collegeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the college file.");
        return;
    }

    QTextStream in(&collegeFile);
    bool codeExists = false;

    // Check if the college code already exists
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(',');

        if (parts.size() == 2 && parts[0].trimmed() == collegeCode) {
            codeExists = true;
            break;
        }
    }
    collegeFile.close();

    if (codeExists) {
        QMessageBox::critical(this, "Duplicate Code Error", "The specified College Code already exists.");
        return;
    }

    QString newCollegeData = QString("%1,%2").arg(collegeCode, collegeName);

    if (!collegeFile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the college file for writing.");
        return;
    }

    QTextStream out(&collegeFile);
    out << newCollegeData << "\n";  // Append new college data
    collegeFile.close();

    loadCSVCollege(collegeFilePath);
    refreshCollegeCodeComboBox();
    refreshCourseComboBox();
    ui->CollegeCodeCombbox->setCurrentIndex(-1);
    ui->CourseComboBox->setCurrentIndex(-1);

    QMessageBox::information(this, "Success", "College added successfully!");
    clearCollegeInputFields();
}

void MainWindow::on_EditCollege_clicked() {
    QItemSelectionModel *selectionModel = ui->CollegeTable->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select a college to edit.");
        return;
    }

    QSet<int> uniqueRows;
    for (const QModelIndex &index : selectedIndexes) {
        uniqueRows.insert(index.row());
    }

    if (uniqueRows.size() > 1) {
        QMessageBox::critical(this, "Selection Error", "Please select only one row to edit.");
        return;
    }

    int selectedRow = *uniqueRows.begin();  // Get the single row index
    QString oldCollegeCode = ui->CollegeTable->model()->data(ui->CollegeTable->model()->index(selectedRow, 0)).toString().trimmed();

    ui->CollegeCodeLine->setText(oldCollegeCode);
    ui->CollegeNameLine->setText(ui->CollegeTable->model()->data(ui->CollegeTable->model()->index(selectedRow, 1)).toString());

    isEditing = true;
    currentEditingRow = selectedRow;
    //ui->AddCollege->setEnabled(false);
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
    ui->CollegeCodeCombbox->setCurrentIndex(-1);
    ui->CourseComboBox->setCurrentIndex(-1);

    QMessageBox::information(this, "Success", "College and related programs updated successfully.");

    ui->CollegeCodeCombbox->clear();
    ui->CourseComboBox->clear();
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
    bool collegeDeleted = false;
    while (!collegeIn.atEnd()) {
        QString line = collegeIn.readLine().trimmed(); // Trim to avoid blank line issues
        if (line.isEmpty()) continue;  // Skip empty lines

        QStringList parts = line.split(',');
        if (!parts.isEmpty() && parts[0].trimmed() == selectedCollegeCode) {
            collegeDeleted = true; // Found and skip this line (delete)
            continue;
        }
        updatedCollegeData.append(line);
    }
    collegeFile.close();

    if (!collegeDeleted) {
        QMessageBox::warning(this, "Deletion Error", "Selected college not found.");
        return;
    }

    if (!collegeFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Unable to write to the college file.");
        return;
    }

    QTextStream collegeOut(&collegeFile);
    for (int i = 0; i < updatedCollegeData.size(); ++i) {
        collegeOut << updatedCollegeData[i];
        if (i != updatedCollegeData.size() - 1) collegeOut << "\n";  //No extra newline at the end
    }
    collegeFile.close();
    loadCSVCollege(collegeFilePath);  // Refresh after deletion
    refreshCollegeCodeComboBox();

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
    for (int i = 0; i < updatedProgramData.size(); ++i) {
        programOut << updatedProgramData[i];
        if (i != updatedProgramData.size() - 1) programOut << "\n";  // Avoid extra newline
    }
    programFile.close();
    loadCSVProgram(programFilePath);  // Refresh programs after update
    refreshCollegeCodeComboBox();


    QMessageBox::information(this, "Success", "Selected college deleted and related programs updated to 'N/A' successfully.");
    ui->CollegeCodeCombbox->setCurrentIndex(-1);
    ui->CourseComboBox->setCurrentIndex(-1);

    ui->CollegeTable->clearSelection(); //Prevent wrong row selection on next deletion
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

    out << "CollegeCode,CollegeName\n";

    for (int row = 0; row < collegeModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < collegeModel->columnCount(); ++col) {
            QStandardItem *item = collegeModel->item(row, col);
            QString cellText = item ? item->text() : "";
            // ✅ Handle commas by wrapping text in quotes
            if (cellText.contains(",")) {
                cellText = "\"" + cellText + "\"";
            }
            rowData.append(cellText);
        }
        out << rowData.join(",") << "\n";
    }

    out.flush();
    ui->CollegeCodeCombbox->clear();
    ui->CourseComboBox->clear();
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

        ui->CollegeCodeCombbox->setCurrentIndex(-1);
        ui->CourseComboBox->setCurrentIndex(-1);

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
    clearStudentInputFields();
    clearProgramInputFields();
    clearCollegeInputFields();

    //ui->CollegeCodeCombbox->setCurrentIndex(-1);
    //ui->CourseComboBox->setCurrentIndex(-1);
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

    currentTable->setSelectionBehavior(QAbstractItemView::SelectRows);

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
    int confirm = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete the selected item?",
                                        QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::No) {
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
    clearStudentInputFields();
    clearProgramInputFields();
    clearCollegeInputFields();
}


//Clear
void MainWindow::clearStudentInputFields()
{
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

void MainWindow::refreshCollegeCodeComboBox() {
    ui->CollegeCodeCombbox->clear();
    for (int row = 0; row < collegeModel->rowCount(); ++row) {
        ui->CollegeCodeCombbox->addItem(collegeModel->item(row, 0)->text());
    }
}

void MainWindow::refreshCourseComboBox() {
    ui->CourseComboBox->clear();
    for (int row = 0; row < programModel->rowCount(); ++row) {
        ui->CourseComboBox->addItem(programModel->item(row, 0)->text());
    }
}






















