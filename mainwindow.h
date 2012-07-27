#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <QDebug>
#include "httpmanager.h"
#include "log.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    QPixmap screenShot;
    HttpManager *http;
    explicit MainWindow(HttpManager *httpManager, QWidget *parent = 0);
    ~MainWindow();
    void updateScreenshotLabel();
private:
    QTimer *timer;
    Ui::MainWindow *ui;
private slots:
    void replyHttp(QNetworkReply *reply);
    void screenShotAction();
    void on_start_stop_toggled(bool checked);
};

#endif // MAINWINDOW_H
