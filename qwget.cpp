/*
    Copyright (c) 2012, Alexander Trousevich <trousev@yandex.ru>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <QDebug>
#include "qwget.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCoreApplication>
#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
#include <QTcpSocket>
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
    /*qDebug() << url.toString();
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
    return QByteArray();*/

    QTcpSocket * socket;
    QString request = QString(
            "GET %1/%2\n"
            "Host: %3\n"
            "User-Agent: Mozilla/5.0 (X11; U; Linux i686; ru; rv:1.9b5) Gecko/2008050509 Firefox/3.0b5\n"
            "Accept: text/html\n"
            "Connection: close\n"
            "\n"
                )
            .arg(QString::fromUtf8(url.encodedPath()))
            .arg(QString::fromUtf8(url.encodedQuery()))
            .arg(url.host())
    ;
    qDebug() << request;
    QTcpSocket s;
    s.open(QTcpSocket::ReadWrite);
    if(url.port() == -1) url.setPort(80);
    s.connectToHost(url.host(), url.port());
    if(!s.waitForConnected(2000)) return QByteArray(s.errorString().toUtf8());
    s.waitForConnected(2000);
    s.write(request.toUtf8());
    if(!s.waitForReadyRead(2000)) return QByteArray("ERRREAD");
    QByteArray ans = s.readAll();
    //s.close();
    if(!s.waitForDisconnected(2000)) return QByteArray("ERRDISC");
    return ans;
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

bool QWget::isSucceed()
{
    return ans != QByteArray();
}
