#include <QtGui>
#include "window.h"
#include "widget.h"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    setAccessibleDescription( Window::getFileName() );
    Widget *widget = new Widget(this);

    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(1,1,1,1);
    layout->addWidget(widget, 0, 0);
    setLayout(layout);

//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), widget, SLOT(animate()));

//    timer->start(20);

}

void Window::keyPressEvent(QKeyEvent *e)
{
    if ( e->key() == Qt::Key_Escape ) {
        QApplication::exit();
    }
}

/**
  obtém o proximo nome de arquivo
*/
QString Window::getFileName()
{
    QString nome;
    for (int i=1; i<1000; i++) {
        nome = QString("vlgt_data%1").arg(i, 3, 10, QLatin1Char('0'));
        QString tmp(nome);
        tmp.append(".txt");
        QFile arq(tmp);

        if (!arq.exists())
            break;
    }

    return nome;

}
