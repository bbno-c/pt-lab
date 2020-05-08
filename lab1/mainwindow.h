#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QDial>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool init();
private:
    QPushButton *btn;
    QLCDNumber *nmb;
    QLabel *lab;
    QLineEdit *le;
    QDial *di;
};
#endif // MAINWINDOW_H
