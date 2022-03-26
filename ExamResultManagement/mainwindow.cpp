#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*!
    \brief The database is creating.
*/
void MainWindow::createDatabase(){

    QString currentPath = QDir::currentPath();
    QString dbName = "ManagementData";
    QSqlDatabase db = QSqlDatabase::addDatabase ("QSQLITE");

    db.setDatabaseName(currentPath+"/"+dbName+".db");

    if( !db.open()) {
        qDebug() << "Can't create Database!";
    }
    else{
        qDebug() << "Database Successfully created!";
        createTables();
    }

}

/*!
    \brief After the database is created, the tables are creating.

    Tables : STUDENT,TEACHER,RESULTS
*/
void MainWindow::createTables(){

    QSqlQuery query;

    ////// STUDENT TABLE
    /// student_id, name, surname
    if (!query.exec("CREATE TABLE STUDENTS ( student_id INTEGER NOT NULL, name STRING, surname STRING, PRIMARY KEY (student_id) )")){
        qDebug() << "Can't create table!";
    }
    else{
        qDebug() << "Create table!";
    }

    ////// TEACHER TABLE
    ///  teacher_id, name, surname
    if (!query.exec("CREATE TABLE TEACHERS ( teacher_id INTEGER NOT NULL, name STRING, surname STRING, PRIMARY KEY (teacher_id) )")){
        qDebug() << "Can't create table!";
    }
    else{
        qDebug() << "Create table!";
    }

    ////// RESULTS TABLE
    ///  result_id, result, teacher_id, student_id
    if (!query.exec("CREATE TABLE RESULTS ( result_id INTEGER NOT NULL, result INTEGER, teacher_id INTEGER, student_id INTEGER, PRIMARY KEY (result_id) )")){
        qDebug() << "Can't create table!";
    }
    else{
        qDebug() << "Create table!";
    }
}
