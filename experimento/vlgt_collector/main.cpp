#include <QtGui/QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.setWindowTitle("VLGT Collector");
    w.showFullScreen();
//    w.show();
    

    return a.exec();
}
