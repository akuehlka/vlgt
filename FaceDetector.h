/* 
 * File:   FaceDetector.h
 * Author: andrey
 *
 * Created on 7 de Março de 2012, 18:21
 */

#ifndef FACEDETECTOR_H
#define	FACEDETECTOR_H

#include <iostream>
#include <string>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "GenericDetector.h"
#include "ImageUtils.h"

class FaceDetector: public GenericCascadeDetector {
public:
    FaceDetector();
    FaceDetector(const FaceDetector& orig);
    virtual ~FaceDetector();
    
    cv::Rect getFaceRegion(const cv::Mat& frame);
    cv::Mat getFaceImage(const cv::Mat& frame);
};

#endif	/* FACEDETECTOR_H */

