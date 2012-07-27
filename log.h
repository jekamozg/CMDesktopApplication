#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QSqlRecord>
#include <QVariantMap>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDateTime>

class Log : public QObject
{
    Q_OBJECT
public:
    QSqlDatabase db;
    explicit Log(QObject *parent = 0);
    ~Log();
    QSqlQuery init();
    QString createTableMap(QString tableName, QVariantMap map);
    void httpManagerRequest(QNetworkRequest request, QString data);
    void httpManagerReply(QNetworkReply & reply, QString data = "");
    void httpManagerLog(QVariantMap map);
    QString insertIntoMap(QString tableName, QVariantMap map);
signals:
    
public slots:
    
};

#endif // LOG_H
