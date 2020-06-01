#ifndef VLGTDATAUTILS_H
#define VLGTDATAUTILS_H

#include <vector>
#include <QString>
#include <QStringList>
#include <QFile>
#include "opencv2/core/core.hpp"
#include "ScreenData.h"
#include "EyeData.h"
#include "runningaveragestream.h"

class VlgtDataUtils
{
private:
    QString filePath;
public:
    VlgtDataUtils();
    VlgtDataUtils(QString path);
    std::map<int, EyeData> loadEyeData(QString filename, FixedReference ref, bool smoothData);
    std::vector<ScreenData> loadScreenData(QString filename);
    static cv::Size loadOriginalScreenResolution(QString filename);
    void maxScreenCoords(const std::vector<ScreenData> &data, int *maxx, int *maxy);
};

#endif // VLGTDATAUTILS_H
