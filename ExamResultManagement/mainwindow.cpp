#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createGui();
    createDatabase();
    makeTestData();
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


/*!
    \brief Creating Gui.Widgets are organizing and promoting.

    Tables : STUDENT,TEACHER,RESULTS
*/
void MainWindow::createGui(){

    ////// MAINWINDOW
    ///
    this->setGeometry(0,0,700,700);                         // Mainwindow set geometry.
    this->setMaximumSize(700,700);
    this->setWindowTitle("Exam Result Management System");  // Mainwindow set window title.

    ////// TABWIDGET
    ///
    tabs = new QTabWidget(this);
    tabs->setFixedSize(700, 700);
    tabs->addTab(new QWidget(),"Stundents");
    tabs->addTab(new QWidget(),"Teachers");
    tabs->addTab(new QWidget(),"Results");
    tabs->addTab(new QWidget(),"Students Filtered by Teacher Name");
    tabs->addTab(new QWidget(),"Students Showing Grades");


    ////// Student Tab
    ///
    s_table = new QTableView(tabs->widget(0));
    s_table->setGeometry(QRect(QPoint(150, 20), QSize(400, 340)));          // Set size and location of the table.
    s_modal = new QSqlQueryModel();

    s_addButton = new QPushButton("Student Add", tabs->widget(0));          // Create the button, make "this" the parent
    s_addButton->setGeometry(QRect(QPoint(270, 510), QSize(160, 50)));      // Set size and location of the button.

    s_lblID = new QLabel("Student ID : ",tabs->widget(0));
    s_lblID->setGeometry(QRect(QPoint(160, 380), QSize(160, 30)));          // Set size and location of the label.

    s_lblName = new QLabel("Student Name : ",tabs->widget(0));
    s_lblName->setGeometry(QRect(QPoint(160, 420), QSize(160, 30)));        // Set size and location of the label.

    s_lblSurname = new QLabel("Student Surname : ",tabs->widget(0));
    s_lblSurname->setGeometry(QRect(QPoint(160, 460), QSize(160, 30)));     // Set size and location of the label.

    s_editID = new QLineEdit(tabs->widget(0));
    s_editID->setGeometry(QRect(QPoint(320, 380), QSize(200, 30)));         // Set size and location of the lineEdit.
    s_editID->setValidator( new QIntValidator(0, 100, this) );

    s_editName = new QLineEdit(tabs->widget(0));
    s_editName->setGeometry(QRect(QPoint(320, 420), QSize(200, 30)));       // Set size and location of the lineEdit.

    s_editSurname = new QLineEdit(tabs->widget(0));
    s_editSurname->setGeometry(QRect(QPoint(320, 460), QSize(200, 30)));    // Set size and location of the lineEdit.

    ////// Teacher tab
    ///
    t_table = new QTableView(tabs->widget(1));
    t_table->setGeometry(QRect(QPoint(150, 20), QSize(400, 340)));          // Set size and location of the table.
    t_modal = new QSqlQueryModel();

    t_addButton = new QPushButton("Teacher Add", tabs->widget(1));          // Create the button, make "this" the parent
    t_addButton->setGeometry(QRect(QPoint(270, 510), QSize(160, 50)));      // Set size and location of the button.

    t_lblID = new QLabel("Teacher ID : ",tabs->widget(1));
    t_lblID->setGeometry(QRect(QPoint(160, 380), QSize(160, 30)));          // Set size and location of the label.

    t_lblName = new QLabel("Teacher Name : ",tabs->widget(1));
    t_lblName->setGeometry(QRect(QPoint(160, 420), QSize(160, 30)));        // Set size and location of the label.

    t_lblSurname = new QLabel("Teacher Surname : ",tabs->widget(1));
    t_lblSurname->setGeometry(QRect(QPoint(160, 460), QSize(160, 30)));     // Set size and location of the label.

    t_editID = new QLineEdit(tabs->widget(1));
    t_editID->setGeometry(QRect(QPoint(320, 380), QSize(200, 30)));         // Set size and location of the lineEdit.
    t_editID->setValidator( new QIntValidator(0, 100, this) );

    t_editName = new QLineEdit(tabs->widget(1));
    t_editName->setGeometry(QRect(QPoint(320, 420), QSize(200, 30)));       // Set size and location of the lineEdit.

    t_editSurname = new QLineEdit(tabs->widget(1));
    t_editSurname->setGeometry(QRect(QPoint(320, 460), QSize(200, 30)));    // Set size and location of the lineEdit.

    ////// Reuslt tab
    ///
    r_table = new QTableView(tabs->widget(2));
    r_table->setGeometry(QRect(QPoint(70, 20), QSize(560, 340)));          // Set size and location of the table.
    r_modal = new QSqlQueryModel();

    r_addButton = new QPushButton("Result Add", tabs->widget(2));           // Create the button
    r_addButton->setGeometry(QRect(QPoint(270, 550), QSize(160, 50)));      // Set size and location of the button.

    r_lblID = new QLabel("Result ID : ",tabs->widget(2));
    r_lblID->setGeometry(QRect(QPoint(160, 380), QSize(160, 30)));          // Set size and location of the label.

    r_lblGrade = new QLabel("Result Grade : ",tabs->widget(2));
    r_lblGrade->setGeometry(QRect(QPoint(160, 420), QSize(160, 30)));       // Set size and location of the label.

    r_lblTeacherID = new QLabel("Teacher ID : ",tabs->widget(2));
    r_lblTeacherID->setGeometry(QRect(QPoint(160, 460), QSize(160, 30)));   // Set size and location of the label.

    r_lblStudentID = new QLabel("Student ID : ",tabs->widget(2));
    r_lblStudentID->setGeometry(QRect(QPoint(160, 500), QSize(160, 30)));   // Set size and location of the label.

    r_editID = new QLineEdit(tabs->widget(2));
    r_editID->setGeometry(QRect(QPoint(320, 380), QSize(200, 30)));         // Set size and location of the lineEdit.
    r_editID->setValidator( new QIntValidator(0, 100, this) );

    r_editGrade = new QLineEdit(tabs->widget(2));
    r_editGrade->setGeometry(QRect(QPoint(320, 420), QSize(200, 30)));      // Set size and location of the lineEdit.
    r_editGrade->setValidator( new QIntValidator(0, 100, this) );

    r_editTeacherID = new QLineEdit(tabs->widget(2));
    r_editTeacherID->setGeometry(QRect(QPoint(320, 460), QSize(200, 30)));  // Set size and location of the lineEdit.
    r_editTeacherID->setValidator( new QIntValidator(0, 100, this) );

    r_editStudentID = new QLineEdit(tabs->widget(2));
    r_editStudentID->setGeometry(QRect(QPoint(320, 500), QSize(200, 30)));  // Set size and location of the lineEdit.
    r_editTeacherID->setValidator( new QIntValidator(0, 100, this) );

    ////// Student Filterede By Teacher name tab
    ///
    st_table = new QTableView(tabs->widget(3));
    st_table->setGeometry(QRect(QPoint(100, 20), QSize(500, 340)));         // Set size and location of the table.

    ////// Student Filterede By Teacher name tab
    ///
    sg_table = new QTableView(tabs->widget(4));
    sg_table->setGeometry(QRect(QPoint(100, 20), QSize(500, 340)));         // Set size and location of the table.

    ////// Connect button signal
    ///
    connect(tabs, &QTabWidget::currentChanged, this, &MainWindow::tabsManagement);
    connect(s_addButton, &QPushButton::released, this, &MainWindow::studentAddButton);
    connect(t_addButton, &QPushButton::released, this, &MainWindow::teacherAddButton);
    connect(r_addButton, &QPushButton::released, this, &MainWindow::resultAddButton);
}


/*!
    \brief Creating Test data.
           All data insert into tables.
           Showing the tables.

    Tables : STUDENT,TEACHER,RESULTS
*/
void MainWindow::makeTestData(){
    QSqlQuery query;

    // Set Student test data
    static int studentID[5] = {2,5,8,10,15};
    QString studentName[5] = {"Metin","Samet","Gamze","Sıla","Mike"};
    QString studentSurname[5] = {"Horzum","Gürses","Ugur","Kaya","Tyson"};

    // Set Teacher test data
    static int teacherID[2] = {1,2};
    QString teacherName[2] = {"Veli","Robert"};
    QString teacherSurname[2] = {"Ozdemir","Hawk"};

    // Set Result test data
    static int resultID[10] = {1,2,3,4,5,6,7,8,9,10};
    static int resultGrade[10] = {55,60,70,80,90,100,100,55,45,20};
    static int resultTeacherID[10] = {1,1,1,1,1,2,2,2,2,2};
    static int resultStudentID[10] = {2,5,8,10,15,2,5,8,10,15};

    // Insert student test data
    for ( int i = 0 ; i<5  ; i++ ) {
        if (!query.exec("INSERT INTO [STUDENTS] (student_id , name , surname ) VALUES ('"+QString::number(studentID[i])+"', '"+studentName[i]+"', '"+studentSurname[i]+"')")){
            qDebug() << "Can't insert record!";
        }
    }
    query.prepare("SELECT * FROM [STUDENTS]");
    query.exec();
    s_modal->setQuery(query);
    s_table->setModel(s_modal);

    // Insert teacher test data
    for ( int i = 0 ; i<2  ; i++ ) {
        if (!query.exec("INSERT INTO [TEACHERS] (teacher_id , name , surname ) VALUES ('"+QString::number(teacherID[i])+"', '"+teacherName[i]+"', '"+teacherSurname[i]+"')")){
            qDebug() << "Can't insert record!";
        }
    }
    query.prepare("SELECT * FROM [TEACHERS]");
    query.exec();
    t_modal->setQuery(query);
    t_table->setModel(t_modal);

    // Insert result test data
    for ( int i = 0 ; i<10  ; i++ ) {
        if (!query.exec("INSERT INTO [RESULTS] ( result_id, result, teacher_id, student_id ) VALUES ('"+QString::number(resultID[i])+"', '"+QString::number(resultGrade[i])+"', '"+QString::number(resultTeacherID[i])+"', '"+QString::number(resultStudentID[i])+"')")){
            qDebug() << "Can't insert record!";
        }
    }
    query.prepare("SELECT * FROM [RESULTS]");
    query.exec();
    r_modal->setQuery(query);
    r_table->setModel(r_modal);
}


void MainWindow::studentAddButton(){

}

void MainWindow::teacherAddButton(){

}

void MainWindow::resultAddButton(){

}

void MainWindow::tabsManagement(){

    QSqlQuery query;
    if( tabs->currentIndex() == 0 ){
    }
    else if( tabs->currentIndex() == 1 ){
    }
    else if( tabs->currentIndex() == 2 ){
    }
    else if( tabs->currentIndex() == 3 ){
    }
    else if( tabs->currentIndex() == 4 ){
    }
}
