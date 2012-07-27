#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(HttpManager *httpManager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->http = httpManager;
    http->request("/desktop/");

    //Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(screenShotAction()));
    //
    ui->setupUi(this);

    connect(http->manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyHttp(QNetworkReply*)));
}

void MainWindow::replyHttp(QNetworkReply *reply) {
    qDebug()<<"MainWindowRequest"<<reply->readAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::screenShotAction() {
    screenShot = QPixmap();
    screenShot = QPixmap::grabWindow(QApplication::desktop()->winId());
    updateScreenshotLabel();
    qDebug()<<screenShot.width();
}

void MainWindow::updateScreenshotLabel()
{
    ui->screenShot->setPixmap(screenShot.scaled(ui->screenShot->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::on_start_stop_toggled(bool checked)
{
    if(checked) {
        ui->start_stop->setText("Stop");
        timer->start(1000);
    }
    else {
        ui->start_stop->setText("Start");
        timer->stop();
    }
}

