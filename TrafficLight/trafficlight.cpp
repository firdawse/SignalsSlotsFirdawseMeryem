#include "trafficlight.h"
#include <QWidget>
#include <QLayout>
#include <QRadioButton>


TrafficLight::TrafficLight(QWidget * parent): QWidget(parent){

    //Creatign the widgets
    createWidgets();

    //place Widgets
    placeWidgets();
     startTimer(1000);

}


void TrafficLight::createWidgets()
{

  redlight = new QRadioButton;
  redlight->setEnabled(false);
 redlight->toggle();
  redlight->setStyleSheet("QRadioButton::indicator:checked { background-color: red;}");

  yellowlight = new QRadioButton;
  yellowlight->setEnabled(false);

  yellowlight->setStyleSheet("QRadioButton::indicator:checked { background-color: yellow;}");

  greenlight = new QRadioButton;
  greenlight->setEnabled(false);

  greenlight->setStyleSheet("QRadioButton::indicator:checked { background-color: green;}");

  lights.append(redlight);
  lights.append(yellowlight);
  lights.append(greenlight);
}


void TrafficLight::placeWidgets()
{

  // Placing the widgets
  auto layout = new QVBoxLayout;
  layout->addWidget(redlight);
  layout->addWidget(yellowlight);
  layout->addWidget(greenlight);
  setLayout(layout);
}

void TrafficLight::timerEvent(QTimerEvent *){
index=(index+1)%7;
if(index==5)
    yellowlight->toggle();
else if(index==6||index==0)
    greenlight->toggle();
else
    redlight->toggle();
}

void TrafficLight::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_R)
        index=0;
    else if(e->key() == Qt::Key_Y)
         index=1;
    else if(e->key() == Qt::Key_G)
         index=2;

    lights[index]->toggle();
}

