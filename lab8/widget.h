#ifndef WIDGET_H
#define WIDGET_H

#pragma once
#include <QtWidgets>
#include <QWidget>
#include <QtSql/QtSql>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    bool initForm();
    bool createConnection(const QString&);
    bool addPerson(const QString& name);
    void showRecords();
    bool delAllRecords();
    void showSearched(const QString&);
private:
    QSqlDatabase m_db;
    QLineEdit *addLine;
    QPushButton *addBtn;
    QPushButton *showBtn;
    QPushButton *deleteBtn;
    QPushButton *searchBtn;
    QListWidget *myList;
};
#endif // WIDGET_H
