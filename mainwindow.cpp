#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unary_operations.h"
#include "binary_operations.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      waitingForOperand(true), previousNumber(0),
      currentOperator("+")
{
    ui->setupUi(this);

    // присоединение кнопок набора числа (цифр и точки)
    for (int i = 0; i < ui->glo_digits->count(); i++)
        connect(ui->glo_digits->itemAt(i)->widget(), SIGNAL(clicked()), this, SLOT(digitClicked()));

    // кнопки очистки
    connect(ui->btn_clear, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(ui->btn_clear_entry, SIGNAL(clicked()), this, SLOT(clearClicked()));

    // бинарные операции
    connect(ui->btn_plus, SIGNAL(clicked()), this, SLOT(binaryClicked()));
    connect(ui->btn_minus, SIGNAL(clicked()), this, SLOT(binaryClicked()));
    connect(ui->btn_multiplication, SIGNAL(clicked()), this, SLOT(binaryClicked()));
    connect(ui->btn_division, SIGNAL(clicked()), this, SLOT(binaryClicked()));
    connect(ui->btn_equal, SIGNAL(clicked()), this, SLOT(resultClicked()));

    // унарные
    for (int i = 0; i < ui->glo_trigonometry->count(); i++)
        connect(ui->glo_trigonometry->itemAt(i)->widget(), SIGNAL(clicked()), this, SLOT(unaryClicked()));
    connect(ui->btn_inverse, SIGNAL(clicked()), this, SLOT(unaryClicked()));
    connect(ui->btn_sqrt, SIGNAL(clicked()), this, SLOT(unaryClicked()));
    connect(ui->btn_sign, SIGNAL(clicked()), this, SLOT(unaryClicked()));
}

QString correctNumber(QString number)
{
    if (number == ".")
        number = "0.";
    else if (number == "-.")
        number = "-0.";
    else if (number == "00")
        number = "0";
    else if (number.count('.') > 1)
        number.chop(1);

    return number;
}

void MainWindow::digitClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QLineEdit* display = ui->le_display;
    QString number;

    if (this->waitingForOperand || display->text() == "0")
        number = "";
    else if (display->text() == "-0")
        number = "-";
    else
        number = display->text();

    number += button->text();
    number = correctNumber(number);

    if (waitingForOperand)
        waitingForOperand = false;

    if (number != display->text())
        display->setText(number);
}

void MainWindow::clearClicked()
{
    ui->le_display->setText("0");

    this->previousNumber = 0;
    this->currentOperator = "+";
    this->waitingForOperand = true;
}

void MainWindow::clearEntryClicked()
{
    ui->le_display->setText("0");
    this->waitingForOperand = true;
}

double calculateBinary(double operrand1, double operrand2, QString operation)
{
    if (operation == "*")
        return opMultiplication(operrand1, operrand2);
    else if (operation == "/")
        return opDivision(operrand1, operrand2);
    else if (operation == "+")
        return opAddition(operrand1, operrand2);
    else if (operation == "-")
        return opSubstraction(operrand1, operrand2);
    else return operrand2;
}

double calculateUnary(double operrand, QString operation)
{
    if (operation == "sin")
        return opSin(operrand);
    else if (operation == "cos")
        return opCos(operrand);
    else if (operation == "tan")
        return opTan(operrand);
    else if (operation == "cot")
        return opCot(operrand);
    else if (operation == "1/x")
        return opInversion(operrand);
    else if (operation == "√")
        return opSquareRoot(operrand);
    else if (operation == "-/+")
        return opChangeSign(operrand);
    else
        return operrand;
}

QString toDisplayFormat(double result)
{
    QString formatedResult = QString::number(result, 'f', 15);

    if (formatedResult.contains('.')) {
        while(formatedResult.back() =='0')
            formatedResult.chop(1);
        if(formatedResult.back() =='.')
            formatedResult.chop(1);
    }

    return formatedResult;
}

void MainWindow::unaryClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    double result = calculateUnary(ui->le_display->text().toDouble(), button->text());

    ui->le_display->setText(toDisplayFormat(result));

    if (button->text() != "-/+")
        this->waitingForOperand = true;
}

void MainWindow::binaryClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if (this->waitingForOperand)
        this->previousNumber = ui->le_display->text().toDouble();
    else {
        double result = calculateBinary(this->previousNumber, ui->le_display->text().toDouble(), this->currentOperator);

        this->previousNumber = result;
        ui->le_display->setText(toDisplayFormat(result));
    }

    this->currentOperator = button->text();
    this->waitingForOperand = true;
}

void MainWindow::resultClicked()
{
    double result = calculateBinary(this->previousNumber, ui->le_display->text().toDouble(), this->currentOperator);

    ui->le_display->setText(toDisplayFormat(result));

    this->previousNumber = 0;
    this->waitingForOperand = true;
    this->currentOperator = "+";
}

MainWindow::~MainWindow()
{
    delete ui;
}
