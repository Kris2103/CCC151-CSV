#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QMainWindow>
#include <QLineEdit>
#include <QModelIndex>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QStackedWidget>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Search_clicked();
    void on_AddStudent_clicked();
    void on_AddProgram_2_clicked();
    void on_AddCollege_2_clicked();

    void clearStudentInputFields();
    void clearProgramInputFields();
    void clearCollegeInputFields();

    void on_EditStudent_clicked();
    void on_EditProg_clicked();
    void on_EditCollege_clicked();

    void on_SaveStudent_clicked();
    void on_SaveProg_clicked();
    void on_SaveCollege_clicked();

    void updateStudentCSV();
    void updateProgramCSV();
    void updateCollegeCSV();

    void on_DeleteStudent_clicked();
    void on_DeleteProgram_clicked();
    void on_DeleteCollege_clicked();

    void on_DeleteButton_clicked();
    void refreshCollegeCodeComboBox();
    void refreshCourseComboBox();

    void on_tabWidget_currentChanged(int index);


private:
    Ui::MainWindow *ui;
    QStandardItemModel *studentModel;
    QStandardItemModel *programModel;
    QStandardItemModel *collegeModel;
    QSortFilterProxyModel *studentProxyModel;

    QString currentCSVStudent;
    QString currentCSVProgram;
    QString currentCSVCollege;

    void loadCSVStudents(const QString &filePath = "");
    void loadCSVProgram(const QString &filePath = "");
    void loadCSVCollege(const QString &filePath= "");

    bool isEditing = false;       // Tracks if we are editing a student
    int currentEditingRow = -1;    // Stores the row index of the student being edited

};
#endif // MAINWINDOW_H
