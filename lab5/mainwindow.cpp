#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBrowse_triggered()
{
    QString fileContents;

    const QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"));
    if (fileName.isEmpty())
        return;

    readFileContent(fileName, &fileContents);

    const QFileInfo fi(fileName);
    QDateTime time = fi.birthTime();
    QString type = fi.suffix();

    showData(fileContents, time, type);
}

void MainWindow::readFileContent(QString fileName, QString* fileContents)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        (fileContents)->append(line);
    }
}

void MainWindow::showData(QString cont, QDateTime t, QString ty)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit_2->clear();

    ui->plainTextEdit->appendPlainText(cont);
    ui->plainTextEdit_2->appendPlainText("DOB:\t" + t.toString());
    ui->plainTextEdit_2->appendPlainText("Extension:\t" + ty);
}
