/* 
 * File:   Mouth.h
 * Author: andrey
 *
 * Created on 19 de Março de 2012, 10:59
 */

#ifndef MOUTH_H
#define	MOUTH_H

#include <opencv2/core/core.hpp>

class Mouth: public cv::Rect {
public:
    Mouth();
    Mouth(cv::Rect mouthRectangle);
    Mouth(const Mouth& orig);
    virtual ~Mouth();
    
    bool drawMouth;
    
private:
    cv::Rect mouthBoundary;
    cv::Point mouthCenter;
};

#endif	/* MOUTH_H */

