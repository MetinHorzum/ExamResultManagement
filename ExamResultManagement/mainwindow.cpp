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
    st_listWidget = new QListWidget(tabs->widget(3));
    st_listWidget->setGeometry(QRect(QPoint(100, 20), QSize(500, 340)));         // Set size and location of the table.

    st_Combobox = new QComboBox(tabs->widget(3));
    st_Combobox->setGeometry(QRect(QPoint(250, 380), QSize(200, 50)));       // Set size and location of the Combobox.
    st_Combobox->addItem("Teachers");

    st_searchButton = new QPushButton("Search", tabs->widget(3));           // Create the button
    st_searchButton->setGeometry(QRect(QPoint(270, 450), QSize(160, 50)));      // Set size and location of the button.

    filter = new QSortFilterProxyModel();

    ////// Student Filterede By Teacher name tab
    ///
    sg_table = new QTableView(tabs->widget(4));
    sg_table->setGeometry(QRect(QPoint(100, 20), QSize(500, 340)));         // Set size and location of the table.
    sg_modal = new QSqlQueryModel();

    sg_Combobox = new QComboBox(tabs->widget(4));
    sg_Combobox->setGeometry(QRect(QPoint(250, 380), QSize(200, 50)));       // Set size and location of the Combobox.
    sg_Combobox->addItem("Students");

    sg_searchButton = new QPushButton("Search", tabs->widget(4));           // Create the button
    sg_searchButton->setGeometry(QRect(QPoint(270, 450), QSize(160, 50)));      // Set size and location of the button.

    ////// Connect button signal
    ///
    connect(tabs, &QTabWidget::currentChanged, this, &MainWindow::tabsManagement);
    connect(s_addButton, &QPushButton::released, this, &MainWindow::studentAddButton);
    connect(t_addButton, &QPushButton::released, this, &MainWindow::teacherAddButton);
    connect(r_addButton, &QPushButton::released, this, &MainWindow::resultAddButton);
    connect(st_searchButton, &QPushButton::released, this, &MainWindow::searchTeacherButton);
    connect(sg_searchButton, &QPushButton::released, this, &MainWindow::searchStudentButton);
}


/*!
    \brief Creating Test data.
           All data insert into tables.
           Showing the tables.

    Tables : STUDENT,TEACHER,RESULTS
*/
void MainWindow::makeTestData(){

    QSqlQuery query;

    ////// Insert student test data
    ///
    for ( int i = 0 ; i<5  ; i++ ) {
        if (!query.exec("INSERT INTO [STUDENTS] (student_id , name , surname ) VALUES ('"+QString::number(studentIDBuff[i])+"', '"+studentNameBuff[i]+"', '"+studentSurnameBuff[i]+"')")){
            qDebug() << "Can't insert record!";
        }
        sg_Combobox->addItem(studentNameBuff[i]);       // Adding Students
    }
    query.prepare("SELECT * FROM [STUDENTS]");
    query.exec();
    s_modal->setQuery(query);
    s_table->setModel(s_modal);

    ////// Insert teacher test data
    ///
    for ( int i = 0 ; i<2  ; i++ ) {
        if (!query.exec("INSERT INTO [TEACHERS] (teacher_id , name , surname ) VALUES ('"+QString::number(teacherIDBuff[i])+"', '"+teacherNameBuff[i]+"', '"+teacherSurnameBuff[i]+"')")){
            qDebug() << "Can't insert record!";
        }
        st_Combobox->addItem(teacherNameBuff[i]);       // Adding Teachers
    }
    query.prepare("SELECT * FROM [TEACHERS]");
    query.exec();
    t_modal->setQuery(query);
    t_table->setModel(t_modal);

    ////// Insert result test data
    ///
    for ( int i = 0 ; i<10  ; i++ ) {
        if (!query.exec("INSERT INTO [RESULTS] ( result_id, result, teacher_id, student_id ) VALUES ('"+QString::number(resultIDBuff[i])+"', '"+QString::number(resultGradeBuff[i])+"', '"+QString::number(resultTeacherIDBuff[i])+"', '"+QString::number(resultStudentIDBuff[i])+"')")){
            qDebug() << "Can't insert record!";
        }
    }
    query.prepare("SELECT * FROM [RESULTS]");
    query.exec();
    r_modal->setQuery(query);
    r_table->setModel(r_modal);
    sg_modal->setQuery(query);
    sg_table->setModel(sg_modal);
}


void MainWindow::studentAddButton(){

    QSqlQuery query;

    int id = s_editID->text().toInt();
    QString name = s_editName->text();
    QString surname = s_editSurname->text();
    if( id != 0 && name != "" && surname != ""){
        if (!query.exec("INSERT INTO [STUDENTS] (student_id , name , surname ) VALUES ('"+QString::number(id)+"', '"+name+"', '"+surname+"')")){
            qDebug() << "Can't insert record!";
            msgBox.information(this,tr("Warning!"),tr("Please enter different ID"));
        }
        else{
            msgBox.information(this,tr("Warning!"),tr("Succesfully Added"));
        }
        sg_Combobox->addItem(name);
    }
    else{
        msgBox.information(this,tr("Warning!"),tr("Please enter information"));
    }

    query.prepare("SELECT * FROM [STUDENTS]");
    query.exec();
    s_modal->setQuery(query);
    s_table->setModel(s_modal);
}

void MainWindow::teacherAddButton(){

    QSqlQuery query;

    int id = t_editID->text().toInt();
    QString name = t_editName->text();
    QString surname = t_editSurname->text();
    if( id != 0 && name != "" && surname != ""){
        if (!query.exec("INSERT INTO [TEACHERS] (teacher_id , name , surname ) VALUES ('"+QString::number(id)+"', '"+name+"', '"+surname+"')")){
            qDebug() << "Can't insert record!";
            msgBox.information(this,tr("Warning!"),tr("Please enter different ID"));
        }
        else{
            msgBox.information(this,tr("Warning!"),tr("Succesfully Added"));
        }
        st_Combobox->addItem(name);
    }
    else{
        msgBox.information(this,tr("Warning!"),tr("Please enter information"));
    }

    query.prepare("SELECT * FROM [TEACHERS]");
    query.exec();
    t_modal->setQuery(query);
    t_table->setModel(t_modal);
}

void MainWindow::resultAddButton(){
    QSqlQuery query;

    int id = r_editID->text().toInt();
    int grade = r_editGrade->text().toInt();
    int t_id = r_editTeacherID->text().toInt();
    int s_id = r_editStudentID->text().toInt();

    if( id != 0 && grade != 0 && t_id != 0 && s_id != 0 ){
        if (!query.exec("INSERT INTO [RESULTS] (result_id, result, teacher_id, student_id ) VALUES ('"+QString::number(id)+"', '"+QString::number(grade)+"', '"+QString::number(t_id)+"', '"+QString::number(s_id)+"')")){
            qDebug() << "Can't insert record!";
            msgBox.information(this,tr("Warning!"),tr("Please enter different ID"));
        }
        else{
            msgBox.information(this,tr("Warning!"),tr("Succesfully Added"));
        }
    }
    else{
        msgBox.information(this,tr("Warning!"),tr("Please enter information"));
    }

    query.prepare("SELECT * FROM [RESULTS]");
    query.exec();
    r_modal->setQuery(query);
    r_table->setModel(r_modal);
}

void MainWindow::searchTeacherButton(){

    QSqlQuery query;
    QString studentName;
    int studentId;
    QString teacherName;
    int teacherId;

    filter->setSourceModel(s_modal);
    s_table->setModel(filter);

    teacherName = st_Combobox->currentText();
    teacherId = st_Combobox->currentIndex();

    st_listWidget->clear();

    if( st_Combobox->currentIndex() != 0 ){
        if( query.exec("SELECT * FROM [RESULTS]")){
             qDebug() << "Can't Execute Query !";
        }
        while(query.next()){
            if( teacherId == query.value(2).toInt() ){
                studentId = query.value(3).toInt();
                st_listWidget->addItem(studentNameBuff[studentId-1]);
            }
        }
    }
    else{
        msgBox.information(this,tr("Warning!"),tr("Please select Teacher Name"));
    }
}

void MainWindow::searchStudentButton(){

    QSqlQuery query;
    QMessageBox msgBox;
    QString studentName;
    int studentId;

    filter->setSourceModel(sg_modal);
    sg_table->setModel(filter);

    studentName = sg_Combobox->currentText();
    studentId = sg_Combobox->currentIndex();

    if( sg_Combobox->currentIndex() != 0 ){
        filter->setFilterRegularExpression(QString::number(studentIDBuff[studentId-1]));
    }
    else{
        msgBox.information(this,tr("Warning!"),tr("Please select Student Name"));
    }
}



void MainWindow::tabsManagement(){

    QSqlQuery query;
    if( tabs->currentIndex() == 0 ){
        s_editID->clear();
        s_editName->clear();
        s_editSurname->clear();
    }
    else if( tabs->currentIndex() == 1 ){
        t_editID->clear();
        t_editName->clear();
        t_editSurname->clear();
    }
    else if( tabs->currentIndex() == 2 ){
        r_editID->clear();
        r_editGrade->clear();
        r_editStudentID->clear();
        r_editTeacherID->clear();
    }
    else if( tabs->currentIndex() == 3 ){
        st_listWidget->clear();
        st_Combobox->setCurrentIndex(0);
    }
    else if( tabs->currentIndex() == 4 ){
        sg_Combobox->setCurrentIndex(0);
        query.prepare("SELECT * FROM [RESULTS]");
        query.exec();
        sg_modal->setQuery(query);
        sg_table->setModel(sg_modal);
    }
}
