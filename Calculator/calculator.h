#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLCDNumber>
#include <QTextBlock>
#include <QLabel>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    int * left=nullptr;          //left operand
    int * right;         // right operand
    QString *operation=nullptr;  // Pointer on the current operation
    int * store =nullptr;
    QString *storeoperation=nullptr;
    QString *bracket1=nullptr;
    QString *bracket2=nullptr;

public slots:
   void newDigit();
   void changeOperation();
   void enterSlot();
   void resetSlot();
   void clearSlot();
   void parenthesis1Slot();
   void parenthesis2Slot();

 // Add you custom slots here

protected:
    void createWidgets();        //Function to create the widgets
    void placeWidget();         // Function to place the widgets
    void makeConnexions();
    void result();// Create all the connectivity


//events
protected:
    void keyPressEvent(QKeyEvent *e)override;     //Override the keypress events

private:
    QGridLayout *buttonsLayout; // layout for the buttons
    QVBoxLayout *layout;        //main layout for the button
    QVector<QPushButton*> digits;  //Vector for the digits
    QPushButton *enter;            // enter button
    QVector<QPushButton*> operations; //operation buttons
    QLCDNumber *disp;             // Where to display the numbers
    QPushButton *reset;
    QTextBlock * TextBlock;
    QPushButton *clear ;  //clear button
    QPushButton *parenthesis1;
    QPushButton *parenthesis2;
    QLabel *label;
    QString form ="";


};
#endif // CALCULATOR_H
