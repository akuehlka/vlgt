/* 
 * File:   PointRunningAverageStream.h
 * Author: andrey
 *
 * Created on 21 de Novembro de 2012, 20:34
 */

#ifndef POINTRUNNINGAVERAGESTREAM_H
#define	POINTRUNNINGAVERAGESTREAM_H

class PointRunningAverageStream {
public:
    PointRunningAverageStream();
    PointRunningAverageStream(const PointRunningAverageStream& orig);
    PointRunningAverageStream(int size);
    virtual ~PointRunningAverageStream();
    cv::Point getPoint(cv::Point pt);
private:
    int maxSampleSize;
    bool smoothX;
    bool smoothY;
    std::vector<cv::Point> sampleQueue;
};

#endif	/* POINTRUNNINGAVERAGESTREAM_H */

