#include "mainwindow.h"

#include <QGridLayout>

#include <QColor>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    if(!setupUi())
        return;
}

MainWindow::~MainWindow()
{
}

bool MainWindow::setupUi()
{
    QGridLayout* grid = new QGridLayout(this);

    color = new QPushButton("Color",this);
    font = new QPushButton("Font",this);

    connect(color, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(font, SIGNAL(clicked()), this, SLOT(changeFont()));

    grid->addWidget(color,0,0,1,1);
    grid->addWidget(font,1,0,1,1);

    QWidget *widget = new QWidget();
    widget->setLayout(grid);
    setCentralWidget(widget);

    return true;
}

void MainWindow::changeColor()
{
    QColor clr = QColorDialog::getColor();
    if(!clr.isValid())
        return;
    color->setStyleSheet("background-color: " + clr.name());
    font->setStyleSheet("background-color: " + clr.name());
}

void MainWindow::changeFont()
{
    bool ok;
    QFont fnt = QFontDialog::getFont(&ok, this);
    if(!ok)
        return;
    color->setFont(fnt);
    font->setFont(fnt);
}

