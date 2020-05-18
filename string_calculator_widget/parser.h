#ifndef PARSER_BASIC_OPERANDS_H
#define PARSER_BASIC_OPERANDS_H

#include <qstack.h>

class Parser_basic_operands
{
public:
    Parser_basic_operands(QString*);
private:
    QString* input_string;
    QString str_result, str_operands;
    QStack<QChar> operators;
    QStack<float> numbers;

    int prior(QChar);
public:
    void parse();
    float get_str();
};

#endif // PARSER_BASIC_OPERANDS_H
