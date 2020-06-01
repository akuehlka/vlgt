#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName("Andrey Kuehlkamp");
    QCoreApplication::setApplicationName("VLGT Processor");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
