#include "parser.h"
#include <QChar>

Parser_basic_operands::Parser_basic_operands(QString* inp):input_string(inp)
{

}

void Parser_basic_operands::parse()
{
    QChar cur_char;
    bool flag;
    while (!input_string->isEmpty()) {

        cur_char = input_string->at(0);
        input_string->remove(0,1);

        if (cur_char == ' ') {
            if(flag) {
                str_result += ' ';
                flag=false;
            }
            continue;
        }

        if(cur_char.isDigit()) {
            str_result += cur_char;
            flag=true;
            continue;
        }

        switch (cur_char.unicode()) {
            case '(' :
                operators.push(cur_char);
            break;
            case '*': case '/': case '+': case '-':
                if (input_string->at(0).isDigit()) {
                    str_result += cur_char;
                    while(!input_string->isEmpty()){
                        if(!input_string->at(0).isDigit())break;
                        cur_char = input_string->at(0);
                        input_string->remove(0,1);
                        str_result += cur_char;
                    }break;
                }
                if (operators.isEmpty()) {
                    operators.push(cur_char);
                    break;
                }
                while((prior(cur_char) <= prior(operators.top()))) {
                    str_result += operators.pop();
                    if(operators.isEmpty()){
                        operators.push(cur_char);
                        break;
                    }
                }
                if(prior(cur_char) > prior(operators.top())) {
                    operators.push(cur_char);
                }
            break;
            case ')':
                while((cur_char = operators.pop()) != '(') {
                    str_result += cur_char;
                }
            break;
        }
    }
    while (!operators.isEmpty()) {
        str_result += operators.pop();
    }

    flag=false;
    QString temp;
    while (!str_result.isEmpty()) {

        cur_char = str_result.at(0);
        str_result.remove(0,1);

        if (cur_char == ' ') {
            continue;
        }

        if(cur_char.isDigit()) {
            temp += cur_char;
            while (str_result.at(0).isDigit()) {
                cur_char = str_result.at(0);
                str_result.remove(0,1);
                temp += cur_char;
            }
            numbers.push(temp.toFloat());
            temp.clear();
            continue;
        }

        switch (cur_char.unicode()) {
            case '*':
                numbers.push(numbers.pop()*numbers.pop());
            break;
            case '/': {
                float second = numbers.pop();
                float first = numbers.pop();
                numbers.push(first/second);
            }
            break;
            case '+':
                numbers.push(numbers.pop()+numbers.pop());
            break;
            case '-':{
                if (!str_result.isEmpty()) {
                    if (str_result.at(0).isDigit()) {
                        temp += cur_char;
                        while(!str_result.isEmpty() && !flag){
                            if(!str_result.at(0).isDigit())
                            {
                                flag=true;
                                continue;
                            }
                            cur_char = str_result.at(0);
                            str_result.remove(0,1);
                            temp += cur_char;
                        }
                        numbers.push(temp.toFloat());
                        temp.clear();
                        flag=false;
                        break;
                    }
                }
                float second = numbers.pop();
                float first = numbers.pop();
                numbers.push(first-second);
            }
            break;
        }

    }
}

int Parser_basic_operands::prior(QChar oper)
{
    switch(oper.unicode()) {
        case '(': return 1;
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        default: return 0;
    }
}

float Parser_basic_operands::get_str()
{
    if (!numbers.isEmpty()) {
        return numbers.pop();
    }
    return 0;
}
