#ifndef STR_CALCULATOR_WIDGET_H
#define STR_CALCULATOR_WIDGET_H

#include "parser.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QtWidgets>
#include <QLabel>

class Button;

class str_calculator_widget : public QWidget
{
    Q_OBJECT

private:

    QString inp_string;
    QLabel* display2;
    QLineEdit *display;
    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];
    bool waitingForOperand;
    bool lock;
    int numOfBrackets;
    Button* createButton(const QString &text, const char *member);

private slots:

    void digitClicked();
    void additiveOperatorClicked();
    void equalClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clearAll();
    void clear();
    void bracketOperatorClicked();

public:
    str_calculator_widget(QWidget *parent = nullptr);
    ~str_calculator_widget();
};
#endif // STR_CALCULATOR_WIDGET_H
