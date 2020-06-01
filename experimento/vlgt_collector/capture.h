#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include <QWidget>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

QT_BEGIN_NAMESPACE
class Widget;
QT_END_NAMESPACE

class Capture : public QWidget
{
    Q_OBJECT
public:
    explicit Capture(QWidget *parent = 0);
    void captureFrame(Widget *parent);
    void writeFrame();

private:
    cv::VideoCapture camera;
    cv::VideoWriter outputVideo;
    cv::Mat frame;
    cv::Mat cvtFrame;
    
signals:
    
public slots:
    
};

#endif // VIDEOCAPTURE_H
