/* 
 * File:   NoseDetector.h
 * Author: andrey
 *
 * Created on 17 de Março de 2012, 14:34
 */

#ifndef NOSEDETECTOR_H
#define	NOSEDETECTOR_H

#include "GenericDetector.h"

class NoseDetector: public GenericCascadeDetector {
public:
    NoseDetector();
    NoseDetector(const NoseDetector& orig);
    virtual ~NoseDetector();
    
    cv::Rect getNoseRegion(const cv::Mat& frame);
    cv::Mat getNoseImage(const cv::Mat& frame);
private:

};

#endif	/* NOSEDETECTOR_H */

