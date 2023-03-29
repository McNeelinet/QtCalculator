#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "operations.h"
#include <stdexcept>
#include <QMessageBox>

const double BTN_FONT_WIDTH_K = 4.8;
const double BTN_FONT_HEIGHT_K = 3.6;
const double LE_FONT_WIDTH_K = 6;
const double LE_FONT_HEIGHT_K = 26;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), memoryEnabled(false), memoryCell(0),
      waitingForOperand(true), previousNumber(0), currentOperator("")
{
    ui->setupUi(this);

    for (int i = 0; i < ui->glo_digits->count(); i++)
        connect(ui->glo_digits->itemAt(i)->widget(), SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->btn_sign, SIGNAL(clicked()), this, SLOT(signClicked()));

    connect(ui->btn_clear, SIGNAL(clicked()), this, SLOT(clearClicked()));
<<<<<<< HEAD
    connect(ui->btn_clear_entry, SIGNAL(clicked()), this, SLOT(clearEntryClicked()));
=======
    connect(ui->btn_del, SIGNAL(clicked()), this, SLOT(delClicked()));

    connect(ui->btn_mem_clear, SIGNAL(clicked()), this, SLOT(memoryClearClicked()));
    connect(ui->btn_mem_save, SIGNAL(clicked()), this, SLOT(memorySaveClicked()));
    connect(ui->btn_mem_read, SIGNAL(clicked()), this, SLOT(memoryReadClicked()));
    connect(ui->btn_mem_plus, SIGNAL(clicked()), this, SLOT(memoryPlusClicked()));
    connect(ui->btn_mem_minus, SIGNAL(clicked()), this, SLOT(memoryMinusClicked()));
>>>>>>> 3e5ebfd (ВЫНЕСЕНА бизнес-логика)

    for (int i = 0; i < ui->glo_trigonometry->count(); i++)
        connect(ui->glo_trigonometry->itemAt(i)->widget(), SIGNAL(clicked()), this, SLOT(unaryClicked()));
    connect(ui->btn_inverse, SIGNAL(clicked()), this, SLOT(unaryClicked()));
    connect(ui->btn_sqrt, SIGNAL(clicked()), this, SLOT(unaryClicked()));

    for (int i = 0; i < ui->glo_binary->count(); i++)
        connect(ui->glo_binary->itemAt(i)->widget(), SIGNAL(clicked()), this, SLOT(binaryClicked()));
    connect(ui->btn_result, SIGNAL(clicked()), this, SLOT(resultClicked()));
}



/*========== Обработка ошибок ==========*/
void MainWindow::logicErrorAction(const char* what)
{
    QMessageBox::critical(qobject_cast<QMainWindow*>(parent()), "Арифметическая ошибка", what);
    this->waitingForOperand = true;
}



/*========= Изменение размеров =========*/
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



/*========== Ввод-вывод чисел ==========*/
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

<<<<<<< HEAD
    this->waitingForOperand = true;
=======
    if (number == "-")
        number = "-0";
    else if (number == "")
        number = "0";

    ui->le_display->setText(number);
>>>>>>> 0e2108a (прибрался. waitingForOperrand - рудимент?)
}

void MainWindow::clearClicked()
{
    ui->le_display->setText("0");

    this->previousNumber = 0;
    this->currentOperator = "";
    this->waitingForOperand = true;
}


<<<<<<< HEAD
<<<<<<< HEAD
=======
// Операции с памятью
=======

/*========= Операции с памятью =========*/
>>>>>>> 0e2108a (прибрался. waitingForOperrand - рудимент?)
void MainWindow::memoryClearClicked()
{
    this->memoryEnabled = false;
    this->memoryCell = 0;
}

void MainWindow::memorySaveClicked()
{
    this->memoryEnabled = true;
    this->memoryCell = ui->le_display->text().toDouble();
}

void MainWindow::memoryReadClicked()
{
    if (this->memoryEnabled) {
        ui->le_display->setText(toDisplayFormat(this->memoryCell));
        this->waitingForOperand = true;
    }
}

void MainWindow::memoryPlusClicked()
{
    this->memoryEnabled = true;
    this->memoryCell = calculate(memoryCell, ui->le_display->text().toDouble(), "+");
}

void MainWindow::memoryMinusClicked()
{
    this->memoryEnabled = true;
    this->memoryCell = calculate(memoryCell, ui->le_display->text().toDouble(), "-");
}


<<<<<<< HEAD
>>>>>>> 3e5ebfd (ВЫНЕСЕНА бизнес-логика)
// Математические операции
=======

/*=========== Кнопки действий ==========*/
>>>>>>> 0e2108a (прибрался. waitingForOperrand - рудимент?)
void MainWindow::binaryClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if (this->waitingForOperand || this->currentOperator == "")
        this->previousNumber = ui->le_display->text().toDouble();
    else {
        try {
            double result = calculate(this->previousNumber, ui->le_display->text().toDouble(), this->currentOperator.toStdString());

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
        double result = calculate(ui->le_display->text().toDouble(), button->text().toStdString());

        ui->le_display->setText(toDisplayFormat(result));
    }
    catch (const std::logic_error& e) {
        logicErrorAction(e.what());
        return;
    }
}

void MainWindow::resultClicked() try  // нежелательно применять function-try так. Просто попробовал...
{
    double result = calculate(this->previousNumber, ui->le_display->text().toDouble(), this->currentOperator.toStdString());

    ui->le_display->setText(toDisplayFormat(result));

    this->previousNumber = 0;
    this->waitingForOperand = true;
    this->currentOperator = "";
}
catch (const std::logic_error& e) {
    logicErrorAction(e.what());
    return;
}



MainWindow::~MainWindow()
{
    delete ui;
}
