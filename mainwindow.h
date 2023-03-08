#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>


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
    void signClicked();
    void clearClicked();
    void clearEntryClicked();
    void resultClicked();
    void binaryClicked();
    void unaryClicked();

private:
    Ui::MainWindow *ui;

    void resizeEvent(QResizeEvent* event);
    void logicErrorAction(const char* what);
    void lengthErrorAction(const char* what);

    bool waitingForOperand;
    double previousNumber;
    QString currentOperator;
};
#endif // MAINWINDOW_H
