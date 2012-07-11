#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPixmap>

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    QPixmap screenShot;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateScreenshotLabel();
private:
    QTimer *timer;
    Ui::MainWindow *ui;
private slots:
    void screenShotAction();
    void on_start_stop_toggled(bool checked);
};

#endif // MAINWINDOW_H
