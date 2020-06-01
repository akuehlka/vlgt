/* 
 * File:   featureFinder.cpp
 * Author: andrey
 * 
 * Created on 17 de Março de 2012, 15:55
 */

#include "FeatureFinder.h"

using namespace std;
using namespace cv;

FeatureFinder::FeatureFinder() {
}

FeatureFinder::FeatureFinder(FinderType ft) {
    this->finderType = ft;
    this->thresholdFactor = 0.5;
    // inicialização dependente do tipo de finder
    // TODO: consertar essa gambiarra
    if (ft == VLGT_FINDER_TYPE_IRIS) {
        this->ffThreshold = 10;
        this->grayScaleCvtType = VLGT_IU_TOGRAY_BLUE;
    }
    if (ft == VLGT_FINDER_TYPE_NOSETIP) {
        this->ffThreshold = 126;
        this->grayScaleCvtType = VLGT_IU_TOGRAY_SIMPLE;
    }
    if (ft == VLGT_FINDER_TYPE_MOUTH) {
        this->ffThreshold = 150;
        this->grayScaleCvtType = VLGT_IU_TOGRAY_GREEN;
    }
}

FeatureFinder::FeatureFinder(const FeatureFinder& orig) {
}

FeatureFinder::~FeatureFinder() {
}




