#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include "capture.h"
#include "window.h"

namespace Ui {
class Widget;
}

// movimentos possíveis na tela.
enum movt{STOP,
          LRT, //left-right on top
          TBR, //top-bottom on right
          RLB, //right-left on bottom
          BTL, //bottom-top on left
          RLTB, //right-left-top-bottom
          RLB2, //right-left on bottom 2
          LRBT, //left-right-bottom-top
          RLT}; //right-left on top

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QPoint origin;
    QImage cam_img;
    Ui::Widget *ui;
    double fps;
    int delayms;

    QFile *outfile;
    QTextStream *ts;

    QString fileName;

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);
    void move(qreal deltat);
    bool mostraTermo();

private slots:
    void on_pushButton_clicked();

private:
    int elapsed;
    QSize size;
    qreal timeslice;
    int stepX;
    int stepY;
    QTime t;
    QTimer *timer;
    double startTicks;
    bool isRecording;
    bool isAnimating;
    bool termAccepted;
    QString userName;
    QString userEmail;

    QTime m_time;
    int m_frameCount;

    movt curr_move;

    Capture *video;


};

#endif // WIDGET_H
