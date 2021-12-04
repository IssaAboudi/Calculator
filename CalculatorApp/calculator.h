#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots: //executed when signal is submitted
    void NumPressed();
    void MathButtonsPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void clear();

    //TODO: add Memory buttons


};
#endif // CALCULATOR_H
