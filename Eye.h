/* 
 * File:   Eye.h
 * Author: andrey
 *
 * Created on 19 de Março de 2012, 10:57
 */

#ifndef EYE_H
#define	EYE_H

#include <opencv2/core/core.hpp>
#include "genericutils.h"
#include "IrisFinder.h"

class Eye: public cv::Rect {
public:
    Eye();
    Eye(cv::Rect eyeRectangle);
    Eye(cv::Rect eyeRectangle, FaceObjType _eyeType);
    virtual ~Eye();

    bool drawEye;
    bool drawIris;
    FaceObjType eyeType;  // esquerdo/direito
    cv::RotatedRect iris;
    cv::Point *leftMostCorner;
    cv::Point *rightMostCorner;
    void setIris(const cv::RotatedRect& i);
    void findIris(const cv::Mat& eyeImage);
    cv::RotatedRect getIris();
    IrisFinder* ifinder;
    void refineROI();
    
};

#endif	/* EYE_H */

