#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "binary_operations.h"
#include "unary_operations.h"
#include <stdexcept>
#include <QMessageBox>

const double BTN_FONT_WIDTH_K = 4.8;
const double BTN_FONT_HEIGHT_K = 3.6;
const double LE_FONT_WIDTH_K = 6;
const double LE_FONT_HEIGHT_K = 26;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      waitingForOperand(true), previousNumber(0),
      currentOperator("")
{
    ui->setupUi(this);

    for (int i = 0; i < ui->glo_digits->count(); i++)
        connect(ui->glo_digits->itemAt(i)->widget(), SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->btn_sign, SIGNAL(clicked()), this, SLOT(signClicked()));

    connect(ui->btn_clear, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(ui->btn_clear_entry, SIGNAL(clicked()), this, SLOT(clearEntryClicked()));

    for (int i = 0; i < ui->glo_trigonometry->count(); i++)
        connect(ui->glo_trigonometry->itemAt(i)->widget(), SIGNAL(clicked()), this, SLOT(unaryClicked()));
    connect(ui->btn_inverse, SIGNAL(clicked()), this, SLOT(unaryClicked()));
    connect(ui->btn_sqrt, SIGNAL(clicked()), this, SLOT(unaryClicked()));

    for (int i = 0; i < ui->glo_binary->count(); i++)
        connect(ui->glo_binary->itemAt(i)->widget(), SIGNAL(clicked()), this, SLOT(binaryClicked()));
    connect(ui->btn_result, SIGNAL(clicked()), this, SLOT(resultClicked()));
}

void MainWindow::logicErrorAction(const char* what)
{
    QMessageBox::critical(qobject_cast<QMainWindow*>(parent()), "Арифметическая ошибка", what);
    this->waitingForOperand = true;
}


// Изменение размеров
void changeFontOnButtons(QLayout* layout)
{
    for (int i = 0; i < layout->count(); i++) {
        QPushButton* button = qobject_cast<QPushButton*>(layout->itemAt(i)->widget());

        if (button != NULL) {
            QFont font = button->font();
            font.setPointSizeF(qMin(button->width() / BTN_FONT_WIDTH_K, button->height() / BTN_FONT_HEIGHT_K));

            button->setFont(font);
        }
    }
}

void changeFontOnDisplay(QLineEdit* lineEdit)
{
    QFont font = lineEdit->font();
    font.setPointSizeF(qMin(lineEdit->height() / LE_FONT_WIDTH_K, lineEdit->width() / LE_FONT_HEIGHT_K));

    lineEdit->setFont(font);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    changeFontOnButtons(ui->glo_digits);
    changeFontOnButtons(ui->glo_operations);
    changeFontOnButtons(ui->glo_binary);
    changeFontOnButtons(ui->glo_memory);
    changeFontOnButtons(ui->glo_trigonometry);

    changeFontOnDisplay(ui->le_display);
}


// Ввод чисел
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

QString correctNumber(QString number)
{
    if (number == ".")
        number = "0.";
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

void MainWindow::signClicked()
{
    QLineEdit* display = ui->le_display;
    QString number = display->text();

    if (number.startsWith("-"))
        number.remove(0, 1);
    else
        number = "-" + number;

    ui->le_display->setText(number);
    this->waitingForOperand = false;
}

void MainWindow::clearEntryClicked()
{
    ui->le_display->setText("0");

    this->waitingForOperand = true;
}

void MainWindow::clearClicked()
{
    ui->le_display->setText("0");

    this->previousNumber = 0;
    this->currentOperator = "";
    this->waitingForOperand = true;
}


// Математические операции
double calculateBinary(double operrand1, double operrand2, std::string operation)
{
    if (operation == "*")
        return opMultiplication(operrand1, operrand2);
    else if (operation == "/")
        return opDivision(operrand1, operrand2);
    else if (operation == "+")
        return opAddition(operrand1, operrand2);
    else if (operation == "-")
        return opSubstraction(operrand1, operrand2);
    else
        throw std::logic_error("Неизвестная операция.");
}

double calculateUnary(double operrand, std::string operation)
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
    else
        throw std::logic_error("Неизвестная операция.");
}

void MainWindow::binaryClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if (this->waitingForOperand || this->currentOperator == "")
        this->previousNumber = ui->le_display->text().toDouble();
    else {
        try {
            double result = calculateBinary(this->previousNumber, ui->le_display->text().toDouble(), this->currentOperator.toStdString());

            this->previousNumber = result;
            ui->le_display->setText(toDisplayFormat(result));
        }
        catch (const std::logic_error& e) {
            logicErrorAction(e.what());
            return;
        }
    }

    this->currentOperator = button->text();
    this->waitingForOperand = true;
}

void MainWindow::unaryClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    try {
        double result = calculateUnary(ui->le_display->text().toDouble(), button->text().toStdString());

        ui->le_display->setText(toDisplayFormat(result));
    }
    catch (const std::logic_error& e) {
        logicErrorAction(e.what());
        return;
    }
}

void MainWindow::resultClicked()
{
    try {
        double result = calculateBinary(this->previousNumber, ui->le_display->text().toDouble(), this->currentOperator.toStdString());

        ui->le_display->setText(toDisplayFormat(result));
    }
    catch (const std::logic_error& e) {
        logicErrorAction(e.what());
        return;
    }

    this->previousNumber = 0;
    this->waitingForOperand = true;
    this->currentOperator = "";
}


MainWindow::~MainWindow()
{
    delete ui;
}
