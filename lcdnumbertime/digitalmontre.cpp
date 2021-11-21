#include "digitalmontre.h"

digitalmontre::digitalmontre(QWidget *parent) : QWidget(parent)
{
    createwidgets();
    placewidgets();
    startTimer(1000);
}
void digitalmontre::updateTime(){
    auto t= QTime::currentTime();
    hour->display(t.hour());
    minute->display(t.minute());
    seconde->display(t.second());
}
void digitalmontre::timerEvent(QTimerEvent *e){
 updateTime();
}
void digitalmontre::createwidgets(){
hour= new QLCDNumber;
minute= new QLCDNumber;
seconde= new QLCDNumber;

hour->setMinimumHeight(80);
minute->setMinimumHeight(80);
seconde->setMinimumHeight(80);
}
void digitalmontre::placewidgets(){
QLayout *layout= new QHBoxLayout;
layout->addWidget(hour);
layout->addWidget(minute);
layout->addWidget(seconde);
setLayout(layout);
}
