/* 
 * File:   IrisFinder.h
 * Author: andrey
 *
 * Created on 12 de Março de 2012, 16:14
 */

#ifndef IRISDETECTOR_H
#define	IRISDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "FeatureFinder.h"
#include "ImageUtils.h"

class IrisFinder: public FeatureFinder {
public:
    IrisFinder();
    IrisFinder(const IrisFinder& orig);
    virtual ~IrisFinder();
    
    cv::RotatedRect findIris(const cv::Mat& src);
protected:
    double irisBrightnessAlpha;
    double irisBrightnessBeta;

private:
    cv::Mat img;
    bool isNearlyRound(const cv::RotatedRect& iris);
    std::vector<cv::RotatedRect> findEllipses();
    void enhanceImage(const cv::Mat& src);
    cv::RotatedRect findAppropriateEllipse(const std::vector<cv::RotatedRect> &ellipses);
    float circularityCoeff(const cv::RotatedRect& elipse);
};

#endif	/* IRISDETECTOR_H */

