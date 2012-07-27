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
    Log log;
    log.httpManagerRequest(request, postData);
    manager->sendCustomRequest(request, "POST", buffer);
}

void HttpManager::reply(QNetworkReply *reply) {
}


void HttpManager::setHeaders(QNetworkRequest & request, const int size) {
    request.setRawHeader("Content-Type", "text/html");
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    if (size > 0) {
        request.setHeader(QNetworkRequest::ContentLengthHeader, QVariant(size));
    }
}

QString HttpManager::encodeBase64( QString string ) {
    QByteArray text;
    text.append(string);
    return text.toBase64();
}

