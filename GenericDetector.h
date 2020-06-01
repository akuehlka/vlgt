/* 
 * File:   GenericDetector.h
 * Author: andrey
 *
 * Created on 10 de Março de 2012, 11:10
 */

#ifndef GENERICDETECTOR_H
#define	GENERICDETECTOR_H

#include <exception>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "ImageUtils.h"

using namespace cv;

class GenericCascadeDetector {
public:
    GenericCascadeDetector();
    GenericCascadeDetector(std::string haarCascadeName);
    GenericCascadeDetector(const GenericCascadeDetector& orig);
    virtual ~GenericCascadeDetector();
protected:
    std::string cascadeName;
    cv::CascadeClassifier cascade;
    cv::Rect processFrame(const cv::Mat& frame);
    cv::Rect getRegion(const cv::Mat& frame);
    cv::Mat getImage(const cv::Mat& frame);
};

#endif	/* GENERICDETECTOR_H */

