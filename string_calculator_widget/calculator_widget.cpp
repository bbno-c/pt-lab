#include "calculator_widget.h"
#include "button.h"

str_calculator_widget::str_calculator_widget(QWidget *parent)
    : QWidget(parent), waitingForOperand(true), lock(false), numOfBrackets(0)
{
    display = new QLineEdit("0");

    display->setReadOnly(true);
    display->setAlignment(Qt::AlignCenter);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    display2 = new QLabel;
    display2->setAlignment(Qt::AlignCenter);
    display->setMaxLength(30);
    font = display2->font();
    font.setPointSize(font.pointSize() + 5);
    display2->setFont(font);

    for (int i = 0; i < NumDigitButtons; ++i)
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));

    Button *changeSignButton = createButton(tr("\302\261"), SLOT(changeSignClicked()));

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    Button *clearButton = createButton(tr("Clear"), SLOT(clear()));
    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));

    Button *divisionButton = createButton(tr("/"), SLOT(additiveOperatorClicked()));
    Button *timesButton = createButton(tr("*"), SLOT(additiveOperatorClicked()));
    Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));

    Button *left_bracket = createButton(tr("("), SLOT(bracketOperatorClicked()));
    Button *right_bracket = createButton(tr(")"), SLOT(bracketOperatorClicked()));

    Button *equalButton = createButton(tr("="), SLOT(equalClicked()));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(display2, 0, 0, 1, 5);
    mainLayout->addWidget(display, 1, 0, 1, 5);

    mainLayout->addWidget(backspaceButton, 2, 0, 1, 2);
    mainLayout->addWidget(clearButton, 2, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 2, 4);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 4;
        int column = ((i - 1) % 3);
        mainLayout->addWidget(digitButtons[i], row, column);
    }
    mainLayout->addWidget(digitButtons[0], 7, 0);
    mainLayout->addWidget(changeSignButton, 4, 3);
    mainLayout->addWidget(equalButton, 5, 3, 3, 1);

    mainLayout->addWidget(divisionButton, 4, 4);
    mainLayout->addWidget(timesButton, 5, 4);
    mainLayout->addWidget(minusButton, 6, 4);
    mainLayout->addWidget(plusButton, 7, 4);

    mainLayout->addWidget(left_bracket, 7, 1);
    mainLayout->addWidget(right_bracket, 7, 2);

    setLayout(mainLayout);

    setWindowTitle(tr("Oleg the Calculator"));
}

str_calculator_widget::~str_calculator_widget()
{
}

Button *str_calculator_widget::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void str_calculator_widget::digitClicked()
{
    if (lock) return;
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;
    else if (display->text() == "0") {
        display->setText(QString::number(digitValue));
    } else {
        display->setText(display->text() + QString::number(digitValue));
    }
}

void str_calculator_widget::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void str_calculator_widget::additiveOperatorClicked()
{

    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;

    if(lock) {
        display2->setText(display2->text() + ' ' + clickedButton->text() + ' ');
        lock=false;
        return;
    }
    if (waitingForOperand) {
        display2->clear();
        waitingForOperand=false;
    }

    display2->setText(display2->text() + display->text() + ' ' + clickedButton->text() + ' ');
    display->clear();
    display->setText("0");
}

void str_calculator_widget::equalClicked()
{
    if (display2->text().isEmpty() || numOfBrackets>0) {
        return;
    }
    if (display->text() != "0") {
        display2->setText(display2->text() + display->text());
    }
    inp_string = display2->text();
    Parser_basic_operands* parser = new Parser_basic_operands(&inp_string);
    parser->parse();
    display2->clear();
    display2->setText(QString::number(parser->get_str()));
    display->setText("0");
    waitingForOperand=true;
    if(lock)lock=false;
}

void str_calculator_widget::backspaceClicked()
{
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
    }
    display->setText(text);
}

void str_calculator_widget::clear()
{
    display->setText("0");
}

void str_calculator_widget::clearAll()
{
    display->setText("0");
    display2->setText("");
    lock=false;
    waitingForOperand=false;
}

void str_calculator_widget::bracketOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString bracket = clickedButton->text();

    if (!clickedButton)
      return;

    if (waitingForOperand) {
        display2->clear();
        waitingForOperand=false;
    }

    if(bracket == "(" && !lock) {
        display2->setText(display2->text() + bracket);
        numOfBrackets++;
    } else if (bracket == ")" && numOfBrackets > 0) {
        if(lock){
            display2->setText(display2->text() + bracket);
            numOfBrackets--;
            lock=true;
            return;
        }
        display2->setText(display2->text() + display->text() + bracket);
        display->clear();
        display->setText("0");
        lock = true;
        numOfBrackets--;
    }
}
