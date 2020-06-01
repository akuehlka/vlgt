/* 
 * File:   Mouth.cpp
 * Author: andrey
 * 
 * Created on 19 de Março de 2012, 10:59
 */

#include "Mouth.h"

using namespace cv;
using namespace std;

Mouth::Mouth() {
}

Mouth::Mouth(cv::Rect mouthRectangle): Rect(mouthRectangle), drawMouth(true) {
}

Mouth::~Mouth() {
}

