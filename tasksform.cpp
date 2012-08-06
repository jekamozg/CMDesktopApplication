#include "tasksform.h"
#include "ui_tasksform.h"

TasksForm::TasksForm(HttpManager *httpManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TasksForm)
{
    this->http = httpManager;
    ui->setupUi(this);
}

TasksForm::~TasksForm()
{
    delete ui;
}
