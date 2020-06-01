/* 
 * File:   featureFinder.h
 * Author: andrey
 *
 * Created on 17 de Março de 2012, 15:55
 */

#ifndef FEATUREFINDER_H
#define	FEATUREFINDER_H

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImageUtils.h"
#include "genericutils.h"

class FeatureFinder {
public:
    FeatureFinder();
    FeatureFinder(FinderType ft);
    FeatureFinder(const FeatureFinder& orig);
    virtual ~FeatureFinder();
    

protected:
    int grayScaleCvtType;
    int ffThreshold;
    int finderType;
    cv::Mat img;
    double thresholdFactor;
    
};

#endif	/* FEATUREFINDER_H */

