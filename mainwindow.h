#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <QDebug>
#include "tasksform.h"
#include "httpmanager.h"
#include "log.h"
#include "qt-json/json.h"

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
    void on_projects_activated(const QString &arg1);
    void on_projects_activated(int index);
    void on_taskDialog_accepted();
    void on_taskDialog_rejected();
};

#endif // MAINWINDOW_H
