#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QSqlQueryModel>

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

    void tabsManagement();

    void studentAddButton();

    void teacherAddButton();

    void resultAddButton();

  private:

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
    QTableView *st_table;

    /**** STUDENT SHOWING GRADES ****/
    QTableView *sg_table;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
