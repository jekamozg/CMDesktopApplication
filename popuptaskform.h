#ifndef POPUPTASKFORM_H
#define POPUPTASKFORM_H

#include <QFrame>

namespace Ui {
class PopupTaskForm;
}

class PopupTaskForm : public QFrame
{
    Q_OBJECT
    
public:
    explicit PopupTaskForm(QWidget *parent = 0);
    ~PopupTaskForm();
    
private:
    Ui::PopupTaskForm *ui;
};

#endif // POPUPTASKFORM_H
