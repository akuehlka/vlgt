/* 
 * File:   EyeDetector.h
 * Author: andrey
 *
 * Created on 10 de Março de 2012, 09:38
 */

#ifndef EYEDETECTOR_H
#define	EYEDETECTOR_H

#include <string>
#include <opencv2/objdetect/objdetect.hpp>
#include "ImageUtils.h"
#include "GenericDetector.h"

enum e_eye {leftEye, rightEye};

class EyeCascadeDetector: public GenericCascadeDetector {;
public:
    EyeCascadeDetector(e_eye eye);
    EyeCascadeDetector(const EyeCascadeDetector& orig);
    virtual ~EyeCascadeDetector();

    cv::Rect getEyeRegion(const cv::Mat& frame);
    cv::Mat getEyeImage(const cv::Mat& frame);
    
    e_eye eyeDet;
};

#endif	/* EYEDETECTOR_H */

