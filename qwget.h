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
    QNetworkAccessManager * manager;
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
    void onFinished(QNetworkReply*);
};

#endif // WGET_H
