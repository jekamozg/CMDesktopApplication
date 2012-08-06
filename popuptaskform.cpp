#include "popuptaskform.h"
#include "ui_popuptaskform.h"

PopupTaskForm::PopupTaskForm(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PopupTaskForm)
{
    ui->setupUi(this);
}

PopupTaskForm::~PopupTaskForm()
{
    delete ui;
}
