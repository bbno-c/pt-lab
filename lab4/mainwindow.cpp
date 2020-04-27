#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextStream"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitPool("city_pool.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (this->ui->lineEdit->text().size() == 0) {
        return;
    }

    if (!m_usedCity.empty())
    {
        auto itCity = std::find_if(m_usedCity.begin(), m_usedCity.end(),
                                    [&](QString City)
                                    {
                                        if(City.toLower() == this->ui->lineEdit->text().toLower()){return true;}
                                        return false;
                                    });

        if(this->ui->lineEdit->text().front().toLower() != m_usedCity.back().back().toLower() || itCity != m_usedCity.end())
        {qInfo() << this->ui->lineEdit->text().front().toLower() << " " << m_usedCity.last().back().toLower(); return; }
    }

    this->ui->plainTextEdit->appendPlainText("Player: " + this->ui->lineEdit->text() + "\0");
    m_playerText = this->ui->lineEdit->text();
    this->ui->lineEdit->clear();
    CompTurn(m_playerText);
}

void MainWindow::InitPool(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        m_compCityPool.push_back(line);
    }
}

void MainWindow::CompTurn(QString playerText)
{
    QString lastSymbol = playerText.back().toLower();
    m_usedCity.append(playerText.toLower());

    auto it = std::find_if(m_compCityPool.begin(), m_compCityPool.end(),
                                [&](QString City)
                                {
                                    if(City.remove(City.size()-1,1).toLower() == playerText.toLower())
                                    {return true;}
                                    return false;
                                });
    m_compCityPool.erase(it);

    auto itCity = std::find_if(m_compCityPool.begin(), m_compCityPool.end(),
                                [&](QString City)
                                {
                                    if(City.front().toLower() == lastSymbol)
                                    {return true;}
                                    return false;
                                });
    auto itExist = std::find_if(m_compCityPool.begin(), m_compCityPool.end(),
                                [&](QString City)
                                {

                                    if(City.remove(City.size()-1,1).toLower() == playerText.toLower())
                                    {qInfo() << City.remove(City.size(),1).toLower() << " " << playerText.toLower();
                                        return true;}
                                    return false;
                                });

    if (itExist == m_compCityPool.end())
    {
        m_newCity.append(playerText);
    }
    if (itCity != m_compCityPool.end())
    {
        this->ui->plainTextEdit->appendPlainText("Comp:" + *itCity + "\0");
        m_usedCity.append((*itCity).remove((*itCity).size()-1,1));
    }
    else
    {
        this->ui->plainTextEdit->appendPlainText("Comp: Я не знаю города на букву " + lastSymbol + "\0");
        this->ui->plainTextEdit->appendPlainText("=GAME OVER=\0");
        this->ui->pushButton->setDisabled(true);

        QFile file("city_pool.txt");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
                return;

        QTextStream out(&file);
        for (auto& city : m_newCity)
        {
            out << (city + "\n");
        }
    }

    m_compCityPool.erase(itCity);
}
