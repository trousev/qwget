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
#ifndef WGET_H
#define WGET_H
#include <stdio.h>
#include <stdlib.h>
#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>

class QWget : public QObject
{
    Q_OBJECT
    struct Error
    {
        QString title;
        QString message;
        Error(QString Title, QString Message)
            :title(Title),message(Message)
        {

        }
        void printStackTrace()
        {
            fprintf(stdout,"%s:%s",title.toLocal8Bit().constData(),message.toLocal8Bit().constData());
        }
    };
private:
    QByteArray ans;
    QString _error;
    bool finished;
public:
    /**
     * @brief WGet Constructor.
     * @param parent Standard QT parent :)
     */
    explicit QWget(QObject *parent = 0);
    /**
     * @brief exec -- start downloading url, given in url parameter
     * @param url -- url to download
     * @return ByteArray of downloaded page or QByteArray() at error
     */
    QByteArray exec(QString url)
    {
        return exec(QUrl(url));
    }
    /**
     * @brief exec -- start downloading url, given in url parameter
     * @param url -- url to download
     * @return ByteArray of downloaded page or QByteArray() at error
     */
    QByteArray exec(QUrl url);
    /**
     * @brief operator () -- alias to exec()
     */
    QByteArray operator()(QString url);
    /**
     * @brief isSucceed -- check last connection for success/error state
     * @return true, if last connection was OK and returned data. False otherwise
     */
    bool isSucceed();
    /**
     * @brief error -- Human-readable error description
     */
    QString error();

    /**
     * @brief get static function, which will do all job
     * @param url URL
     * @return ByteArray with downloaded page or QByteArray() at error
     */
    static QByteArray get(QUrl url);
    /**
     * @brief get static function, which will do all job
     * @param url URL
     * @return ByteArray with downloaded page or QByteArray() at error
     */
    static QByteArray get(QString url);

signals:

private slots:
    void onFinished();
};

#endif // WGET_H
