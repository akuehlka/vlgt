#ifndef ESTIMATOR_H
#define ESTIMATOR_H

#include <QString>
#include <QTextStream>
#include <QDateTime>
#include <QTimer>
#include <QFile>
#include <vector>
#include "opencv2/core/core.hpp"
#include "ScreenData.h"
#include "runningaveragestream.h"
#include "porestimator.h"
#include "VideoFile.h"

class Estimator
{
public:
    Estimator();
    Estimator( QString fileName, FixedReference fixRef, cv::Size sz, int RAVGSize );
    ~Estimator();

    static const int SECTOR_COLS = 3;
    static const int SECTOR_ROWS = 2;
    cv::Mat outputImage;
    cv::Mat outputVideo;
    bool hasFrames();
    void drawPOR();
    double maxDist();
    int sectorHits;
    int frameCount;
    double accumError;
    double accumErrorX;
    double accumErrorY;
    double accumErrorDeg;
    double accumErrorDegX;
    double accumErrorDegY;
    double accumTime;

private:
    POREstimator *porEstimator;
    std::vector<ScreenData> estimatedCoordinates;
    std::vector<ScreenData> referenceCoordinates;
    RunningAverageStream rasX;
    RunningAverageStream rasY;
    VideoFile *video;
    cv::Size screenSize;
    cv::Rect sectors[SECTOR_ROWS][SECTOR_COLS];
    cv::Point porPoint;
    cv::Point refPoint;
    int porSector;
    int refSector;
    QFile *outfile;
    QTextStream *textOut;
    void initSectors();
    void initOutFile(QString fileName);
    void drawSectors(const cv::Mat& src, cv::Mat dst);
    void porDrawn();
    
};

#endif // ESTIMATOR_H
