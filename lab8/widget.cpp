#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    if (!initForm())return;

    QString myPath = QCoreApplication::applicationDirPath()+"/people.db";

    if (!createConnection(myPath))
    return;
}

Widget::~Widget()
{
}

bool Widget::initForm()
{
    this->resize(400,300);

    addLine = new QLineEdit(this);
    addLine->move(10,10);

    addBtn = new QPushButton(("Внести данные"),this);
    addBtn->move(150,10);
    connect(addBtn,&QPushButton::clicked,[&](){
        addPerson(addLine->text());
        });

    showBtn = new QPushButton(("Показать записи"),this);
    showBtn->move(10,50);
    connect(showBtn,&QPushButton::clicked,[&](){
        myList->clear();
        showRecords();
        });

    deleteBtn = new QPushButton(("Очистить"),this);
    deleteBtn->move(120,50);
    connect(deleteBtn,&QPushButton::clicked,[&](){
        delAllRecords();
        myList->clear();
        });

    searchBtn = new QPushButton(("Найти"),this);
    searchBtn->move(200,50);
    connect(searchBtn,&QPushButton::clicked,[&](){
        myList->clear();
        showSearched(addLine->text());
        });

    myList = new QListWidget(this);
    myList->move(10,100);
    return true;
}

bool Widget::createConnection(const QString &myPath)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(myPath);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
        return false;
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

    QSqlQuery query;
    query.exec("CREATE TABLE people(ids integer primary key, name text)");
    query.exec("INSERT INFO people values(101, 'Андрей')");
    return true;
}

void Widget::showRecords()
{
    QSqlQuery query("SELECT * FROM people");
    int idName = query.record().indexOf("name");
    while (query.next())
    {
    QString name = query.value(idName).toString();
    myList->addItem(name);
    //qDebug() << name;
    }
}

bool Widget::addPerson(const QString& name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO people (name) VALUES (:name)");
    query.bindValue(":name", name);
    if(query.exec())
    {
    success = true;
    }
    else
    {
    qDebug() << "addPerson error:  "
    << query.lastError();
    }
    return success;
}

bool Widget::delAllRecords()
{
    QSqlQuery query;
    query.prepare("DELETE FROM people");
    query.exec();
    return true;
}

void Widget::showSearched(const QString& value)
{
    QSqlQuery query("SELECT name FROM people WHERE name = '" + value + "'");
    //qDebug() << query.value(0).toString();
    while (query.next())
    {
        QString name = query.value(0).toString();
        myList->addItem(name);
        qDebug() << name;
    }
}
