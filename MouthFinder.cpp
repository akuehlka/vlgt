/* 
 * File:   MouthFinder.cpp
 * Author: andrey
 * 
 * Created on 18 de Março de 2012, 15:48
 */

#include "MouthFinder.h"

using namespace std;
using namespace cv;

MouthFinder::MouthFinder(): FeatureFinder( VLGT_FINDER_TYPE_MOUTH ) {
}

MouthFinder::MouthFinder(const MouthFinder& orig) {
}

MouthFinder::~MouthFinder() {
}

RotatedRect MouthFinder::findMouth(const Mat& src) {
    if (src.channels() < 3)
        throw std::string("Uma imagem com 3 canais era esperada.");
    
//    this->enhanceImage(src);
    
    vector<RotatedRect> result;// = this->findEllipses();
    
    if (result.size() == 0)
        return RotatedRect();
    
    // TODO: escolher a melhor elipse para retornar
    return result[0];
}