#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(HttpManager *httpManager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->http = httpManager;

    //getProjects request
    http->request("/desktop/getProjects");
    //Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(screenShotAction()));
    //
    ui->setupUi(this);
    ui->centralWidget->setUpdatesEnabled(true);
    this->setFixedHeight(this->height());
    this->setFixedWidth(389);
    connect(http->manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyHttp(QNetworkReply*)));
}

void MainWindow::replyHttp(QNetworkReply *reply) {
    QString json = reply->readAll();
    //    qDebug()<<"MainWindowReplyUrl"<<reply->url();

    using namespace QtJson;
    bool success;
    QVariantMap resultMap = Json::parse(json, success).toMap();
    //getProjects
    if(reply->url() == http->getUrl("/desktop/getProjects")) {

        foreach(QString key, resultMap.keys()) {
            QVariant currentProject = resultMap[key];
            QVariantMap map = currentProject.toMap();
            ui->projects->addItem(map["name"].toString(), currentProject);
        }

        //        qDebug()<<"result"<<resultMap;
        //        qDebug()<<"getUrl"<<reply->url()<<http->getUrl("/desktop/getProjects");
    }
    //getTasks
    if(reply->url() == http->getUrl("/desktop/getTasks")) {
        foreach(QString key, resultMap.keys()) {
            QVariant currentProject = resultMap[key];
            QVariantList tasksList = currentProject.toList();
            for(int i = 0; i < tasksList.count(); i++){
                QVariantMap map = tasksList.at(i).toMap();
                ui->tasks->addItem(map["name"].toString(), tasksList.at(i));
            }
        }
    }
    //    qDebug()<<"MainWindowReply"<<json;
    Log log;
    log.httpManagerReply(*reply, json);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::screenShotAction() {
    screenShot = QPixmap();
    screenShot = QPixmap::grabWindow(QApplication::desktop()->winId());
    updateScreenshotLabel();
    //    qDebug()<<screenShot.width();
}

void MainWindow::updateScreenshotLabel()
{
    ui->screenShot->setPixmap(screenShot.scaled(ui->screenShot->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::on_start_stop_toggled(bool checked)
{
    if(checked) {
        ui->start_stop->setText("Stop");

        int projectIndex = ui->projects->currentIndex();
        QVariantMap projectData = ui->projects->itemData(projectIndex).toMap();
        QVariantMap postData;
        postData[projectData["id"].toString()] = projectData["id"].toString();
        http->request("/desktop/getTasks", postData);
        timer->start(1000);


        this->setFixedWidth(ui->centralWidget->width()*2);
    }
    else {
        ui->start_stop->setText("Start");
        timer->stop();
    }
}


void MainWindow::on_projects_activated(const QString &arg1)
{
    qDebug()<<"on_projects_activated"<<arg1;
}

void MainWindow::on_projects_activated(int index)
{
    qDebug()<<"on_projects_activated"<<index;
}

void MainWindow::on_taskDialog_accepted()
{
    this->setFixedWidth(ui->centralWidget->width()/2);
}

void MainWindow::on_taskDialog_rejected()
{
    this->setFixedWidth(ui->centralWidget->width()/2);
}
