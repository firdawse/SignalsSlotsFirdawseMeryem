#include <QApplication>
#include"digitalmontre.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
auto p= new digitalmontre;
p->show();
    return app.exec();
}
