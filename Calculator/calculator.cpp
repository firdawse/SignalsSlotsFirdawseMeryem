#include "calculator.h"
#include <QKeyEvent>
#include <QApplication>
#include <QTextBlock>


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    createWidgets();
    placeWidget();
    makeConnexions();


}

Calculator::~Calculator()
{
    delete disp;
    delete layout;
    delete buttonsLayout;
}


void Calculator::createWidgets()
{
    //Creating the layouts
    layout = new QVBoxLayout();
    layout->setSpacing(2);

    //grid layout
    buttonsLayout = new QGridLayout;

    //creating the buttons
    for(int i=0; i < 10; i++)
    {
        digits.push_back(new QPushButton(QString::number(i)));
        digits.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        digits.back()->resize(sizeHint().width(), sizeHint().height());
    }
    //enter button
    enter = new QPushButton("Enter",this);
    enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    enter->resize(sizeHint().width(), sizeHint().height());

    //clear button
    clear = new QPushButton("clear",this);
    clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    clear->resize(sizeHint().width(), sizeHint().height());

    // "("  button
    parenthesis1 = new QPushButton("(",this);
    clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    clear->resize(sizeHint().width(), sizeHint().height());

    // ")"  button
    parenthesis2 = new QPushButton(")",this);
    clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    clear->resize(sizeHint().width(), sizeHint().height());

    //reset button
     reset = new QPushButton("reset",this);
     reset->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
     reset->resize(sizeHint().width(), sizeHint().height());

    //operatiosn buttons
    operations.push_back(new QPushButton("+"));
    operations.push_back(new QPushButton("-"));
    operations.push_back(new QPushButton("*"));
    operations.push_back(new QPushButton("/"));
    operations.push_back(new QPushButton("!"));

    //creating the lcd
    disp = new QLCDNumber(this);
    label = new QLabel(this);
    label->setStyleSheet("QLabel { background-color :white; color : black; }");
    QFont font = label->font();
    font.setPointSize(20);
    font.setBold(true);
    label->setFont(font);

    disp->setDigitCount(6);

}

void Calculator::placeWidget()
{
      layout->addWidget(label);
    layout->addWidget(disp);

    layout->addLayout(buttonsLayout);


    //adding the buttons
    for(int i=1; i <10; i++)
        buttonsLayout->addWidget(digits[i], (i-1)/3, (i-1)%3);


    //Adding the operations
    for(int i=0; i < 5; i++)
        buttonsLayout->addWidget(operations[ i], i, 5);


    //Adding the 0 button
    buttonsLayout->addWidget(digits[0], 3, 0);
    buttonsLayout->addWidget(enter, 4, 0, 1,1);
     buttonsLayout->addWidget(clear, 4, 1, 1,1);

     buttonsLayout->addWidget(reset, 4,2 ,1,1);
      buttonsLayout->addWidget(parenthesis1,3,1,1,1);
      buttonsLayout->addWidget(parenthesis2,3,2,1,1);

    setLayout(layout);
}

void Calculator::makeConnexions()
{
    //Connecting the digits
    for(int i=0; i <10; i++)
        connect(digits[i], &QPushButton::clicked,
                this, &Calculator::newDigit);

    //Connecting the operations
    for(int i=0; i <5; i++)
        connect(operations[i], &QPushButton::clicked,
                this, &Calculator::changeOperation);

    connect(enter, &QPushButton::clicked,
            this, &Calculator::enterSlot);
    connect(parenthesis1, &QPushButton::clicked,
                this, &Calculator::parenthesis1Slot);

    connect(parenthesis2, &QPushButton::clicked,
                this, &Calculator::parenthesis2Slot);

    connect(clear, &QPushButton::clicked,
            this, &Calculator::clearSlot);

    connect(reset, &QPushButton::clicked,
            this, &Calculator::resetSlot);
}



void Calculator::newDigit(){
    //Getting the identity of the button using dynamic_cast
    auto button  = dynamic_cast<QPushButton*>(sender());

    // Each button has his own digit in the text
    auto value = button->text().toInt();

    if(!operation){

        if(!left)
        left = new int{value};
        else
        *left=*left*10+value;

     disp->display(*left);

     //to siplay all the expression in QLabel
     form=form+QString::number(value);
     label->setText(form);

    }else {
           if(!right)
                right = new int{value};
           else
                *right = 10 * (*right) + value;

              disp->display(*right);

              form=form+QString::number(value);
              label->setText(form);

              //this process will help us making multiple operations
                if(*operation == "+"){
                    *left=*right+*left;
                }else if(*operation == "-"){
                   *left=*left-*right;
                }else if(*operation == "*"){
                     *left=*left*(*right);
                }else if(*operation == "/"){
                    if(*right==0){
                         disp->display("error");}
                     else{*left=*left/(*right);}
                }
    }

}



void Calculator::changeOperation()
{
    //Getting the sender button
        auto button = dynamic_cast<QPushButton*>(sender());

        //Storing the operation
        operation = new QString{button->text()};

        //Initiating the right button
        right = new int{0};

        //reseting the display
        disp->display(0);
        form=form+(*operation);
        label->setText(form);

        //operation !
        if(*operation=="!"){
            int r=1;
            for(int i=1;i<=*left;i++){
                r=r*i;
            }
            *left=r;
        }

}
void Calculator::enterSlot(){

   disp->display(*left);

}

void Calculator::keyPressEvent(QKeyEvent *e)
{
    //Exiting the application by a click on space
    if( e->key() == Qt::Key_Escape)
        qApp->exit(0);


    //You could add more keyboard interation here (like digit to button)
}



void Calculator::clearSlot(){
     if(operation){
            if(*operation == "+"){
                *left=*left-*right;
            }else if(*operation == "-"){
               *left=*left+*right;
            }else if(*operation == "*"){
                if(*right==0){
                      disp->display("error");}
            else{ *left=*left/(*right);}

            }else if(*operation == "/"){
                 *left=*left*(*right);
            }
      }
   disp->display(0);

    }
void Calculator::parenthesis1Slot(){
    if(left && operation){
    store=new int{*left};
    storeoperation= new QString{*operation};
    left = nullptr;
    operation=nullptr;
    }
    disp->display(0);
    form=form+"(";
    label->setText(form);

}
void Calculator::parenthesis2Slot(){
    if(store){
    if(*storeoperation == "+"){
        *left=*store+*left;
    }else if(*storeoperation == "-"){
       *left=*store-*left;
    }else if(*storeoperation == "*"){
        *left=*store*(*left);
    }else if(*storeoperation == "/"){
        if(*left==0){disp->display("error");}
         else {*left=*store/(*left);}
    }
   }
  disp->display(0);
  form=form+")";
  label->setText(form);
}
void Calculator::resetSlot(){
    right = new int{0};
    left = new int{0};
    //reseting the display
    disp->display(0);
    form="";
    label->setText(form);
}
