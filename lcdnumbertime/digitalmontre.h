#ifndef DIGITALMONTRE_H
#define DIGITALMONTRE_H

#include <QWidget>
#include<QTimerEvent>
#include<QLabel>
#include<QTime>
#include<QLCDNumber>
#include<QHBoxLayout>
class digitalmontre : public QWidget
{
    Q_OBJECT
public:
    explicit digitalmontre(QWidget *parent = nullptr);

protected:
     void timerEvent(QTimerEvent *e)override;
void createwidgets();
void placewidgets();
void updateTime();
private:
QLabel *time;
QLCDNumber *hour;
QLCDNumber *minute;
QLCDNumber *seconde;

};

#endif // DIGITALMONTRE_H
