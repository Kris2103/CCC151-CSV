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
    void on_tabWidget_currentChanged();
    void on_Search_clicked();
    void on_Add_clicked();

    void on_Edit_clicked();
    void sortStudents();

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
};
#endif // MAINWINDOW_H
