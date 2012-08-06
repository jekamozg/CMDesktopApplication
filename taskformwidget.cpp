#include "taskformwidget.h"
#include "ui_taskformwidget.h"

TaskFormWidget::TaskFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskFormWidget)
{
    ui->setupUi(this);
}

TaskFormWidget::~TaskFormWidget()
{
    delete ui;
}
