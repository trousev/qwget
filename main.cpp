#include <QCoreApplication>
#include "qwget.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QWget w;
    return a.exec();
}
