#include "qwget.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCoreApplication>
#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
QWget::QWget(QObject *parent) :
    QObject(parent)
{

    finished = false;
}
QByteArray QWget::operator ()(QString url)
{
    return exec(url);
}

QByteArray QWget::exec(QUrl url)
{
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));
    QNetworkRequest * nr = new QNetworkRequest(url);
    finished = false;
    manager->get(*nr);
    while(!finished)
    {
        QCoreApplication::instance()->processEvents();
        #ifdef WIN32
        Sleep(50);
        #else
            usleep(50000);
        #endif
    }
    delete nr;
    delete manager;
    QCoreApplication::instance()->processEvents();
    return ans;
    return QByteArray();
}

void QWget::onFinished(QNetworkReply * reply)
{
    _error = reply->errorString();
    ans = reply->readAll();
    finished = true;
}

QString QWget::error()
{
    return _error;
}
QByteArray QWget::get(QString url)
{
    return get(QUrl(url));
}
QByteArray QWget::get(QUrl url)
{
    QWget wget;
    return wget.exec(url);
}
