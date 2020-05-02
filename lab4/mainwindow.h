#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLinkedList>

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *        ui;
    QLinkedList<QString>    m_compCityPool;
    QLinkedList<QString>    m_usedCity;
    QLinkedList<QString>    m_newCity;
    QString                 m_playerText;

    void                InitPool(QString fileName);
    void                CompTurn(QString playerText);

    void writeNewCity();
};
#endif // MAINWINDOW_H
