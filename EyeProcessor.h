/* 
 * File:   EyeProcessor.h
 * Author: andrey
 *
 * Created on 15 de Julho de 2012, 15:47
 */

#ifndef EYEPROCESSOR_H
#define	EYEPROCESSOR_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "BlobDetector.h"
#include "Face.h"
#include "Eye.h"
#include "PointRunningAverageStream.h"

class EyeProcessor {
public:
    EyeProcessor();
    EyeProcessor(const EyeProcessor& orig);
    virtual ~EyeProcessor();
    
    int refineEyeWindows(Face& face);
    void findCorners(Face& face);
    void locateCorners(Face& face);
    void locateIris(const cv::Mat& src, cv::Mat& dst);
    void applySobel(const cv::Mat& src, cv::Mat& dst);
    void probabilisticHough(const cv::Mat& src, cv::Mat& dst);
    void newLocateCorners(Face& face);
private:
    cv::Mat borderPreservingFilter(const cv::Mat& img, int type, cv::Point* peak, const cv::Mat& mask);
    cv::Mat getEyeContourMask(const cv::Mat& img);
    cv::Mat segmentSclera(const cv::Mat& img);
    cv::Rect getRefinedEyeWindow(const Eye& eye);
    cv::Rect getLeftCornerWindow(const Eye& eye);
    cv::Rect getRightCornerWindow(const Eye& eye);
    void skeletonize(const cv::Mat& _img, cv::Mat& _dst);
    float GetSlope(cv::Point2f pt1, cv::Point2f pt2);
    void openAndErode(const cv::Mat& src, cv::Mat& dst);
    cv::Point bottomRightMost(const cv::Mat& src);
    int i;
    int houghCirclesThreshold;
    int houghLinesThreshold;
    PointRunningAverageStream lcavg;
    PointRunningAverageStream rcavg;

};

#endif	/* EYEPROCESSOR_H */

