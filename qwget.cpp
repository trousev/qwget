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

#include "qwget.h"
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QCoreApplication>
#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

QNetworkAccessManager * __manager = NULL;
QNetworkAccessManager * manager()
{
    if(!__manager)
    {
        __manager = new QNetworkAccessManager;
        __manager->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy,"localhost",8118));
    }
    return __manager;
}

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
    //connect(manager(),SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));
    QNetworkRequest * nr = new QNetworkRequest(url);
    //nr->setRawHeader("User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:7.0.1) Gecko/20100101 Firefox/7.0.1");
    nr->setRawHeader("User-Agent","Opera/9.0");
    finished = false;
    QNetworkReply * reply = manager()->get(*nr);
    connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
    while(!finished)
    {
        QCoreApplication::instance()->processEvents();
        #ifdef WIN32
        Sleep(50);
        #else
            usleep(50000);
        #endif
    }
    QCoreApplication::instance()->processEvents();
    //qDebug() << "Ans: " << ans;
    // delete nr;
    return ans;
    return QByteArray();
}

void QWget::onFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    _error = reply->errorString();
    //qDebug () << "ERR:" << _error;
    ans = reply->readAll();
    finished = true;
}

QString QWget::error()
{
    //qDebug () << "ERR:" << _error;
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
