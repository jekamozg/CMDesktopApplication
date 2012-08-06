#include "log.h"

Log::Log(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setConnectOptions();
    db.setDatabaseName("log.db");
    db.open();
    this->init();
}
//Insert into log table
QString Log::insertIntoMap(QString tableName, QVariantMap map){
    QString fieldString = "INSERT INTO "+tableName+" (";
    QString valueString = "";
    int i = 0;
    foreach(QString key, map.keys()) {
        i++;
        fieldString.append(key);
        valueString.append("'"+map[key].toString()+"'");
        if(map.count() > i) {
            fieldString.append(",");
            valueString.append(",");
        }
    }
    fieldString.append(") VALUES ("+valueString+")");
    return fieldString;
}

//Creating log table
QString Log::createTableMap(QString tableName, QVariantMap map){
    QString fieldString = "CREATE TABLE " + tableName + " (id integer,";
    foreach(QString key, map.keys()) {
        fieldString.append(key+" "+map[key].toString()+",");
    }
    fieldString.append("PRIMARY KEY (id))");
    return fieldString;
}

//Init log tables
QSqlQuery Log::init() {
    QVariantMap httpManagerMap;
    httpManagerMap["url"] = "text";
    httpManagerMap["dateTime"] = "varchar(64)";
    httpManagerMap["type"] = "varchar(64)";
    httpManagerMap["headers"] = "text";
    httpManagerMap["data"] = "text";
    httpManagerMap["statusMessage"] = "text";
    httpManagerMap["status"] = "varchar(64)";
    return db.exec(createTableMap("httpManager", httpManagerMap));
}

void Log::httpManagerRequest(QNetworkRequest request, QString data) {
    QDateTime requestTime = QDateTime();
    QString dateTime = requestTime.currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    QVariantMap httpManagerMap;
    httpManagerMap["url"] = request.url().toString();
    httpManagerMap["dateTime"] = dateTime;
    httpManagerMap["type"] = "request";
    httpManagerMap["headers"] = "";
    httpManagerMap["data"] = data;
    httpManagerMap["statusMessage"] = "";
    httpManagerMap["status"] = "";
    httpManagerLog(httpManagerMap);
}

void Log::httpManagerReply(QNetworkReply & reply, QString data) {
    QDateTime requestTime = QDateTime();
    QString dateTime = requestTime.currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    QVariantMap httpManagerMap;
    httpManagerMap["url"] = reply.url().toString();
    httpManagerMap["dateTime"] = dateTime;
    httpManagerMap["type"] = "reply";
    httpManagerMap["headers"] = "";
    httpManagerMap["data"] = data;
    httpManagerMap["statusMessage"] = reply.errorString();
    httpManagerMap["status"] = reply.error();
    httpManagerLog(httpManagerMap);
}

void Log::httpManagerLog(QVariantMap map) {
    db.exec(this->insertIntoMap("httpManager", map));
//    qDebug()<<"qwe"<<this->insertIntoMap("httpManager", map);
}

Log::~Log()
{
    db.close();
}
