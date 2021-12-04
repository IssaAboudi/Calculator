#include "calculator.h"
#include "ui_calculator.h"
#include <QtWidgets>

double calcValue = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcValue)); //QString cast as number
    QPushButton* numButtons[10];

    for(int i = 0; i < 10; i++){
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton*>(buttonName); //add all buttons from UI to array of buttons
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed())); //calls numPressed when number button are pressed
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonsPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(clear()));
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::NumPressed(){
    QPushButton* button = (QPushButton*)sender();
    QString buttonValue = button->text(); //get number off our q button
    QString displayValue = ui->Display->text();

    //TODO: Fix 0 button not registering
    if(displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0){
        ui->Display->setText(buttonValue);
    } else {
        QString newValue = displayValue + buttonValue; //append numbers together
        double dblNewValue = newValue.toDouble();

        ui->Display->setText(QString::number(dblNewValue, 'g', 16)); //16 characters before turns into exponent view
    }
}

void Calculator::MathButtonsPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayValue = ui->Display->text();
    calcValue = displayValue.toDouble();

    QPushButton* button =(QPushButton*) sender();
    QString buttonValue = button->text(); //get text on the button

    if(QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(buttonValue, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else {
        subTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger) {
            solution = calcValue + dblDisplayValue;
        } else if(subTrigger) {
            solution = calcValue - dblDisplayValue;
        } else if(multTrigger) {
            solution = calcValue * dblDisplayValue;
        } else {
            solution = calcValue / dblDisplayValue;
        }
    }

    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayValue = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    if(reg.match(displayValue).hasMatch()){
        double dblDisplayValue = displayValue.toDouble();
        double dblDisplaySign = -1 * dblDisplayValue;
        ui->Display->setText(QString::number(dblDisplaySign));
    }
}

void Calculator::clear(){
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    if(dblDisplayValue != 0 || dblDisplayValue != 0.0){
        ui->Display->setText(QString::number(0.0));
        calcValue = 0.0;
    }
}
