#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton* color;
    QPushButton* font;

    bool setupUi();

public slots:
    void changeColor();
    void changeFont();
};
#endif // MAINWINDOW_H
