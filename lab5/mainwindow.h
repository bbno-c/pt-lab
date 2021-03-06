#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    void on_actionBrowse_triggered();

private:
    Ui::MainWindow *ui;
    void readFileContent(QString fileName, QString *fileContents);
    void showData(QString, QDateTime, QString);
};
#endif // MAINWINDOW_H
