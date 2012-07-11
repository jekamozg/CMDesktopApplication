#include <QtGui/QApplication>
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow l;

//    MainWindow w;

    l.show();
//    w.show();
    
    return a.exec();
}
