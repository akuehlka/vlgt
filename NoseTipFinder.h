/* 
 * File:   NoseTipFinder.h
 * Author: andrey
 *
 * Created on 18 de Março de 2012, 11:39
 */

#ifndef NOSETIPFINDER_H
#define	NOSETIPFINDER_H

#include "FeatureFinder.h"

class NoseTipFinder : public FeatureFinder {
public:
    NoseTipFinder();
    NoseTipFinder(const NoseTipFinder& orig);
    virtual ~NoseTipFinder();
    
    cv::RotatedRect findNoseTip(const cv::Mat& src);
private:

};

#endif	/* NOSETIPFINDER_H */

