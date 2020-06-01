#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QWidget;
QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    static QString getFileName();
//    QTimer *timer;
    QString fileName;

protected:
    void keyPressEvent(QKeyEvent *e);
    
signals:
    
public slots:
    
};

#endif // WINDOW_H
