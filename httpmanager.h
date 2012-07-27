#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QBuffer>
#include <QDebug>
#include "log.h"

class HttpManager : public QObject
{
    Q_OBJECT
private:
    QString login;
    QString password;
    QString host;
public:
    explicit HttpManager(QObject *parent = 0, QString login = "", QString password = "", QString host = "");
    QNetworkAccessManager *manager;
    void request(QString path = "", QVariantMap map = QVariantMap());
    void setHeaders(QNetworkRequest &request, const int size = 0);
    QString encodeBase64(QString string);
signals:
    
public slots:
    void reply(QNetworkReply *reply);
};

#endif // HTTPMANAGER_H
