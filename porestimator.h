#ifndef PORESTIMATOR_H
#define PORESTIMATOR_H

#include "iostream"
#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include "opencv2/highgui/highgui.hpp"
#include "vlgtdatautils.h"
#include "ScreenData.h"
#include "runningaveragestream.h"

class POREstimator
{
private:
    QString fileName;
    QString filePath;
    cv::Mat polynomial;
    void processEyeLine(QByteArray bline);
    cv::Size screenSize;
public:
    POREstimator();
    POREstimator(QString polynomialFile);
    std::vector<ScreenData> processFile(FixedReference fixRef, int averageSpan);
    void setScreenSize(cv::Size s);
};

#endif // PORESTIMATOR_H
