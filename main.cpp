#include <QCoreApplication>
#include "qwget.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QWget w;
    qDebug() << w.exec("http://regservice1.contourcomponents.com:80/");
    //return a.exec();
}
