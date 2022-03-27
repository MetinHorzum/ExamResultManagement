#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:

    void createGui();

    void createDatabase();

    void createTables();

    void makeTestData();

    void tabsManagement();

    void studentAddButton();

    void teacherAddButton();

    void resultAddButton();

    void searchTeacherButton();

    void searchStudentButton();
private:

    QMessageBox msgBox;

    // Set Student test data
    int studentIDBuff[5] = {2,5,8,10,15};
    QString studentNameBuff[5] = {"Metin","Samet","Gamze","Sıla","Mike"};
    QString studentSurnameBuff[5] = {"Horzum","Gürses","Ugur","Kaya","Tyson"};

    // Set Teacher test data
    int teacherIDBuff[2] = {1,2};
    QString teacherNameBuff[2] = {"Veli","Robert"};
    QString teacherSurnameBuff[2] = {"Ozdemir","Hawk"};

    // Set Result test data
    int resultIDBuff[10] = {1,2,3,4,5,6,7,8,9,10};
    int resultGradeBuff[10] = {55,60,70,80,90,100,100,55,45,20};
    int resultTeacherIDBuff[10] = {1,1,1,1,1,2,2,2,2,2};
    int resultStudentIDBuff[10] = {2,5,8,10,15,2,5,8,10,15};

private:

    QSortFilterProxyModel *filter;
    QTabWidget *tabs;

    /**** STUDENT ****/
    QTableView *s_table;
    QSqlQueryModel *s_modal;
    QPushButton *s_addButton;
    QPushButton *s_deleteButton;
    QLabel      *s_lblID;
    QLabel      *s_lblName;
    QLabel      *s_lblSurname;
    QLineEdit   *s_editID;
    QLineEdit   *s_editName;
    QLineEdit   *s_editSurname;

    /**** TEACHER ****/
    QTableView *t_table;
    QSqlQueryModel *t_modal;
    QPushButton *t_addButton;
    QPushButton *t_deleteButton;
    QLabel      *t_lblID;
    QLabel      *t_lblName;
    QLabel      *t_lblSurname;
    QLineEdit   *t_editID;
    QLineEdit   *t_editName;
    QLineEdit   *t_editSurname;

    /**** RESULT ****/
    QTableView *r_table;
    QSqlQueryModel *r_modal;
    QPushButton *r_addButton;
    QPushButton *r_deleteButton;
    QLabel      *r_lblID;
    QLabel      *r_lblGrade;
    QLabel      *r_lblStudentID;
    QLabel      *r_lblTeacherID;
    QLineEdit   *r_editID;
    QLineEdit   *r_editGrade;
    QLineEdit   *r_editStudentID;
    QLineEdit   *r_editTeacherID;

    /**** STUDENT BY TEACHER NAME ****/
    QListWidget *st_listWidget;
    QComboBox *st_Combobox;
    QPushButton *st_searchButton;

    /**** STUDENT SHOWING GRADES ****/
    QTableView *sg_table;
    QSqlQueryModel *sg_modal;
    QComboBox *sg_Combobox;
    QPushButton *sg_searchButton;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
