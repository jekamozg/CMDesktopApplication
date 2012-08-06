#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>


LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->login->setPlaceholderText("Enter login");
    ui->pass->setPlaceholderText("Enter password");
    ui->pass->setEchoMode(QLineEdit::Password);

    http = new HttpManager(this, "login", "pass", "http://symfony.loc/app_dev.php");

    connect(http->manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyHttp(QNetworkReply*)));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginBox_accepted()
{
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    if(ui->login->text() == "") {
        ui->login->setStyleSheet("border: 1px solid red;");
    }
    else if(ui->pass->text() == "") {
        ui->pass->setStyleSheet("border: 1px solid red;");
    }
    else {
        QVariantMap postData;
        postData["username"] = ui->login->text();
        postData["password"] = ui->pass->text();
        http->request("/desktop/login", postData);
    }
}

void LoginWindow::on_loginBox_rejected()
{
    this->~LoginWindow();
    qDebug()<<"reject";
    exit(0);
}

void LoginWindow::replyHttp(QNetworkReply *reply) {
    QString json = reply->readAll();
    Log log;
    log.httpManagerReply(*reply, json);
    qDebug()<<"replyData"<<json;
    using namespace QtJson;
    bool ok;
    //json is a QString containing the JSON data
    QVariantMap result = Json::parse(json, ok).toMap();
    if(result.contains("id")) {
        MainWindow *mainWindow = new MainWindow(http);
        mainWindow->show();
        qDebug()<<"accept";
        this->close();
        this->disconnect(http->manager, SIGNAL(finished(QNetworkReply*)),
                         this, SLOT(replyHttp(QNetworkReply*)));
        //        this->~LoginWindow();
    }
    else {
        ui->message->setText("Wrong login or password");
    }
    qDebug()<<"DATA\n"<<result;
    qDebug()<<"HEADERS\n"<<reply->rawHeaderPairs();
}
