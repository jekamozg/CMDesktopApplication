#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "mainwindow.h"
#include "httpmanager.h"
#include "qt-json/json.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT
private:
    HttpManager *http;
public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
private slots:
    void replyHttp(QNetworkReply *reply);
    void on_loginBox_accepted();
    void on_loginBox_rejected();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
