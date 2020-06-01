/* 
 * File:   NoseTipFinder.cpp
 * Author: andrey
 * 
 * Created on 18 de Março de 2012, 11:39
 */

#include <opencv2/highgui/highgui.hpp>

#include "NoseTipFinder.h"

using namespace std;
using namespace cv;

NoseTipFinder::NoseTipFinder(): 
FeatureFinder( VLGT_FINDER_TYPE_NOSETIP ) 
{
}

NoseTipFinder::NoseTipFinder(const NoseTipFinder& orig) {
}

NoseTipFinder::~NoseTipFinder() {
}

RotatedRect NoseTipFinder::findNoseTip(const Mat& src) {
    if (src.channels() < 3)
        throw std::string("Uma imagem com 3 canais era esperada.");
    
//imshow("debug", src);
//    this->enhanceImage(src);
    
    vector<RotatedRect> result;// = this->findEllipses();
    
    if (result.size() == 0)
        return RotatedRect();
    
    // TODO: escolher a melhor elipse para retornar
    return result[0];
}