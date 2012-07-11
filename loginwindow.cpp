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

//    QVariantMap postData;

//    postData["login"] = "";
//    postData["pass"] = "";

//    http->request("/desktop/login", postData);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginBox_accepted()
{
    QVariantMap postData;

    postData["login"] = ui->login->text();
    postData["pass"] = ui->pass->text();

    http->request("/desktop/login", postData);
}

void LoginWindow::on_loginBox_rejected()
{
    this->~LoginWindow();
    qDebug()<<"reject";
    exit(0);
}

void LoginWindow::replyHttp(QNetworkReply *reply) {
    QString json = reply->readAll();

    using namespace QtJson;

    bool ok;
    //json is a QString containing the JSON data
    QVariantMap result = Json::parse(json, ok).toMap();

    if(result["success"] == true) {
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
        qDebug()<<"accept";
    }
    else if(result["success"] == false) {
        ui->message->setText(result["message"].toString());
    }

    qDebug()<<"DATA\n"<<result;
    qDebug()<<"HEADERS\n"<<reply->rawHeaderPairs();
}
