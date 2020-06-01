#ifndef VLGTVIDEOCALIBRATOR_H
#define VLGTVIDEOCALIBRATOR_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "EyeData.h"
#include "ScreenData.h"
#include "CalibrationPair.h"
#include "ScreenPoint.h"
#include "LeastSquaresSolver.h"
#include "vlgtdatautils.h"

class VlgtVideoCalibrator
{
private:
    QString filepath;
    int polynomialDegree;
    int maxx, maxy;
    std::vector<ScreenData> screen;
    std::map<int, EyeData> eye;
    std::vector<CalibrationPair> calibrationPairs;
    void calibrate(QString filename, FixedReference fixRef);
    void processScreenLine(QByteArray line);
    void max(int *maxx, int *maxy);
    ScreenPoint isROI(ScreenData coord);
    EyeData readEyeCoordinates(int frame, QFile *file);
    void showCalibrationPairs();
    void showEyeData();
public:
    VlgtVideoCalibrator();
    VlgtVideoCalibrator(QString path, int polydeg);
    void calibrateQueue(QStringList files, FixedReference fixRef);
};

#endif // VLGTVIDEOCALIBRATOR_H
