/* 
 * File:   Eye.cpp
 * Author: andrey
 * 
 * Created on 19 de Março de 2012, 10:57
 */

#include "Eye.h"
#include "IrisFinder.h"

using namespace cv;
using namespace std;

Eye::Eye()
 : leftMostCorner(0),
   rightMostCorner(0)
{
}

Eye::Eye(Rect eyeRectangle)
 : Rect(eyeRectangle), 
   drawEye(true),
   drawIris(true) {
}

Eye::Eye(cv::Rect eyeRectangle, FaceObjType _eyeType)
 : eyeType(_eyeType), 
   Rect(eyeRectangle), 
   drawEye(true),
   drawIris(true),
   leftMostCorner(NULL),
   rightMostCorner(NULL)
{
}

Eye::~Eye() {
}

void Eye::setIris(const RotatedRect& i) {
    this->iris = i;
}

RotatedRect Eye::getIris() {
    return this->iris;
}

void Eye::findIris(const Mat& eyeImage) {
//    IrisFinder ifinder;
    RotatedRect iris = ifinder->findIris( eyeImage );
    
    this->setIris(iris);
}

void Eye::refineROI() {
    if (this->iris.boundingRect().area() != 0 ) {
        int h = this->iris.boundingRect().height * 1.3;
        int w = MIN( this->iris.boundingRect().width * 3.2, this->width*0.9 );
        int x = this->iris.center.x - (w/2); // ligeiramente para a esquerda
        int y = this->iris.center.y - (h/2)*0.8; // ligeiramente para cima
        
        this->x += x;
        this->y += y;
        this->width = w;
        this->height = h;
        
        //isto já é gambiarra
        this->iris.center.x -= x;
        this->iris.center.y -= y;
    }
}