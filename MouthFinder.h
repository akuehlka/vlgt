/* 
 * File:   MouthFinder.h
 * Author: andrey
 *
 * Created on 18 de Março de 2012, 15:48
 */

#ifndef MOUTHFINDER_H
#define	MOUTHFINDER_H

#include <opencv2/core/core.hpp>
#include "FeatureFinder.h"

class MouthFinder: public FeatureFinder {
public:
    MouthFinder();
    MouthFinder(const MouthFinder& orig);
    virtual ~MouthFinder();

    cv::RotatedRect findMouth(const cv::Mat& src);
private:

};

#endif	/* MOUTHFINDER_H */

