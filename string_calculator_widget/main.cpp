#include "calculator_widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    str_calculator_widget w;
    w.show();
    return a.exec();
}
