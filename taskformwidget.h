#ifndef TASKFORMWIDGET_H
#define TASKFORMWIDGET_H

#include <QWidget>

namespace Ui {
class TaskFormWidget;
}

class TaskFormWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TaskFormWidget(QWidget *parent = 0);
    ~TaskFormWidget();
    
private:
    Ui::TaskFormWidget *ui;
};

#endif // TASKFORMWIDGET_H
