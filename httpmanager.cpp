#include "httpmanager.h"

HttpManager::HttpManager(QObject * parent, QString login, QString password, QString host) : manager(new QNetworkAccessManager(parent)),
    QObject(parent)
{
    this->host = host;
    this->login = login;
    this->password = password;
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
//    QString json = reply->readAll();

//    using namespace QtJson;

//    bool ok;
//    //json is a QString containing the JSON data
//    QVariantMap result = Json::parse(json, ok).toMap();

//    qDebug()<<"DATA\n"<<result;
//    qDebug()<<"HEADERS\n"<<reply->rawHeaderPairs();
}


void HttpManager::setHeaders(QNetworkRequest & request, const int size) {
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
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

