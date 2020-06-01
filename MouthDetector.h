/* 
 * File:   MouthDetector.h
 * Author: andrey
 *
 * Created on 18 de Março de 2012, 15:17
 */

#ifndef MOUTHDETECTOR_H
#define	MOUTHDETECTOR_H

#include "GenericDetector.h"

class MouthDetector: public GenericCascadeDetector {
public:
    MouthDetector();
    MouthDetector(const MouthDetector& orig);
    virtual ~MouthDetector();
    
    cv::Rect getMouthRegion(const cv::Mat& frame);
    cv::Mat getMouthImage(const cv::Mat& frame);
private:

};

#endif	/* MOUTHDETECTOR_H */

