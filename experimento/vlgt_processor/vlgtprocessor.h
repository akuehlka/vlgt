#ifndef VLGTPROCESSOR_H
#define VLGTPROCESSOR_H

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <opencv2/highgui/highgui.hpp>
#include "VideoFile.h"
#include "Face.h"
#include "FaceDetector.h"
#include "EyeDetector.h"
#include "irisfinderwrapper.h"
#include "EyeBlobDetector.h"
#include "genericutils.h"
#include "EyeProcessor.h"
#include "runningaveragestream.h"

class VlgtProcessor : public QObject
{
    Q_OBJECT

public:
    VlgtProcessor();
    VlgtProcessor(QString path, int rasSize);
    ~VlgtProcessor();
    void processQueue(QStringList fileList);
    bool stop;
    cv::Mat outputImage;
    cv::Mat outputEye;
    IrisFinderWrapper ifind;

public slots:
    void setFaceBrightnessAlpha(int value);
    void setFaceBrightnessBeta(int value);
    void setStop(bool value);
    void setRasQueueSize(int value);

private:
    QString filePath;
    void process(QString fileName);
    double faceBrightnessAlpha;
    double faceBrightnessBeta;
    int rasQueueSize;
};

#endif // VLGTPROCESSOR_H
