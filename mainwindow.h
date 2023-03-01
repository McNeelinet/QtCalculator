#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitClicked();
    void clearClicked();
    void clearEntryClicked();

private:
    Ui::MainWindow *ui;

    bool waitingForOperand;
    double previousNumber;
    QString currentOperator;

};
#endif // MAINWINDOW_H
