#include "httpmanager.h"

HttpManager::HttpManager(QObject * parent, QString login, QString password, QString host) : manager(new QNetworkAccessManager(parent)),
    QObject(parent)
{
    this->host = host;
    this->login = login;
    this->password = password;

    connect(this->manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(reply(QNetworkReply*)));

}

void HttpManager::request(QString path, QVariantMap map) {
    QByteArray postData = "";

    foreach(QString key, map.keys()) {
        postData.append(key + "=" + encodeBase64(map[key].toString()) + "&");
    }

    qDebug()<<"map"<<map.keys();
    QNetworkRequest request;
    QBuffer *buffer = new QBuffer(this->parent());
    buffer->setData(postData);

    request.setUrl(QUrl(this->host + path));

    setHeaders(request, buffer->data().length());

    manager->sendCustomRequest(request, "POST", buffer);
}

void HttpManager::reply(QNetworkReply *reply) {
    qDebug()<<"reply_error"<<reply->errorString();
    qDebug()<<"log"<<"qwerty";
}


void HttpManager::setHeaders(QNetworkRequest & request, const int size) {
//    request.setRawHeader("host", "symfony.loc");

//    request.setRawHeader("accept-charset", "windows-1251,utf-8;q=0.7,*;q=0.3");
//    request.setRawHeader("accept-encoding", "gzip,deflate,sdch");
//    request.setRawHeader("accept-language", "ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4");

//    request.setRawHeader("user-agent", "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.57 Safari/536.11");

//    request.setHeader(QNetworkRequest::ContentLengthHeader, 100);

//    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");

    if (size > 0) {
        request.setHeader(QNetworkRequest::ContentLengthHeader, QVariant(size));
    }
    //////qDebug()<<request.rawHeaderList();
}

QString HttpManager::encodeBase64( QString string ) {
    QByteArray text;
    text.append(string);
    return text.toBase64();
}

