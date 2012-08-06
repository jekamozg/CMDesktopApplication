#ifndef TASKSFORM_H
#define TASKSFORM_H

#include <QWidget>

#include "httpmanager.h"
#include "log.h"
#include "qt-json/json.h"

namespace Ui {
class TasksForm;
}

class TasksForm : public QWidget
{
    Q_OBJECT
    
public:
    HttpManager *http;
    explicit TasksForm(HttpManager *httpManager, QWidget *parent = 0);
    ~TasksForm();
    
private:
    Ui::TasksForm *ui;
};

#endif // TASKSFORM_H
