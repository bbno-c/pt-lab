#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    if (!init()) close();
}

MainWindow::~MainWindow()
{
}

bool MainWindow::init()
{
    btn = new QPushButton(this);
    nmb = new QLCDNumber(this);
    lab = new QLabel(this);
    le = new QLineEdit(this);
    di = new QDial(this);

    if (!btn) return false;
    if (!nmb) return false;
    //setCentralWidget(di);

    btn->setText("ok");
    btn->move(10,10);
    btn->resize(100,50);

    nmb->display(11);
    nmb->move(120,10);
    nmb->resize(100,50);

    lab->setText("Lab work 1");
    lab->move(230,10);
    lab->resize(100,50);

    le->move(340,10);
    le->resize(100,50);

    di->move(450,10);
    di->resize(100,50);

    return true;
}

