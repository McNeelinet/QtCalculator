#include "mainwindow.h"
#include "ui_mainwindow.h"


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
}

QString correctNumber(QString number)
{
    if (number == ".")
        number = "0.";
    else if (number == "00")
        number.chop(1);
    else if (number.count('.') > 1)
        number.chop(1);

    return number;
}

void MainWindow::digitClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QLineEdit* display = ui->le_display;
    QString number;

    if (waitingForOperand)
        number = "";
    else
        number = display->text();
    number += button->text();

    number = correctNumber(number);

    if (waitingForOperand && button->text() != "0")
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

MainWindow::~MainWindow()
{
    delete ui;
}
