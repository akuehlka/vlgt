/* 
 * File:   Face.cpp
 * Author: andrey
 * 
 * Created on 19 de Março de 2012, 10:53
 */

#include <opencv2/highgui/highgui.hpp>

#include "Face.h"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>



using namespace std;
using namespace cv;

Face::Face() {
}

Face::Face(Rect faceRectangle): 
    Rect(faceRectangle), 
    drawFace(true),
    drawEyes(true),
    leftEye(0),
    rightEye(0)
{
}

Face::~Face() {
}

Mat Face::getFullFrame() {
    // desenha face
    if (this->area() > 0) 
        if (this->drawFace) {
            Point pt1(this->x, this->y);
            Point pt2(this->x+this->width, this->y+this->height);
            rectangle(this->originalFrame, pt1, pt2, Scalar(255,255,255), 1, 1, 0);
        }
    
    // desenha olho esquerdo
    if (this->leftEye != 0) {
        Point offset = this->getAbsPos(VLGT_FACE_LEFT_EYE);
        if (this->leftEye->area() > 0) {
            if (this->drawEyes) {
                Point pt1(offset);
                Point pt2(pt1.x+this->leftEye->width, pt1.y+this->leftEye->height);
                rectangle(this->originalFrame, pt1, pt2, Scalar(255,255,255), 1, 1, 0);
            }
            if (this->leftEye->drawIris) {
                RotatedRect iris = this->leftEye->getIris();
                iris.center.x += offset.x;
                iris.center.y += offset.y;
                circle(this->originalFrame, iris.center, 2, Scalar(0,0,255), 1, 1, 0);
                ellipse(this->originalFrame, iris, Scalar(0,0,255), 1, 1);
                // desenho também os cantos
                if (this->leftEye->leftMostCorner != NULL &&
                    this->leftEye->rightMostCorner != NULL) {
                    Point lc = *this->leftEye->leftMostCorner;
                    Point rc = *this->leftEye->rightMostCorner;
                    // ajusta o offset
                    lc += offset;
                    rc += offset;
    //                cout << lc << endl;
                    circle(this->originalFrame, lc, 2, Scalar(0,255,0), 1, 1, 0);
                    circle(this->originalFrame, rc, 2, Scalar(0,255,0), 1, 1, 0);
                }
            }
        }
    }
    
    // desenha olho direito
    if (this->rightEye != 0) {
        Point offset = this->getAbsPos(VLGT_FACE_RIGHT_EYE);
        if (this->rightEye->area() > 0 ) {
            if (this->drawEyes) {
                Point pt1(offset);
                Point pt2(pt1.x+this->rightEye->width, pt1.y+this->rightEye->height);
                rectangle(this->originalFrame, pt1, pt2, Scalar(255,255,255), 1, 1, 0);
            }
            if (this->rightEye->drawIris) {
                RotatedRect iris = this->rightEye->getIris();
                Point pt1 = this->getAbsPos(VLGT_FACE_RIGHT_EYE);
                iris.center.x += offset.x;
                iris.center.y += offset.y;
                circle(this->originalFrame, iris.center, 2, Scalar(0,0,255), 1, 1, 0);
                ellipse(this->originalFrame, iris, Scalar(0,0,255), 1, 1);
                // desenho também os cantos
                Point lc = *this->rightEye->leftMostCorner;
                Point rc = *this->rightEye->rightMostCorner;
                // ajusta o offset
                lc += offset;
                rc += offset;
                circle(this->originalFrame, lc, 2, Scalar(0,0,255), 1, 1, 0);
                circle(this->originalFrame, rc, 2, Scalar(0,0,255), 1, 1, 0);
            }
        }
    }
    
    // desenha boca
    if (this->mouth.area() > 0 && this->mouth.drawMouth) {
        Point pt1 = this->getAbsPos(VLGT_FACE_MOUTH);
        Point pt2(pt1.x+this->mouth.width, pt1.y+this->mouth.height);
        rectangle(this->originalFrame, pt1, pt2, Scalar(255,255,255), 1, 1, 0);
    }

    return this->originalFrame;
}

void Face::setLeftEye(Eye *e) {
    this->leftEye = e;
}

Eye* Face::getLeftEye() {
    return this->leftEye;
}

void Face::setRightEye(Eye *e) {
    this->rightEye = e;
}

Eye* Face::getRightEye() {
    return this->rightEye;
}

void Face::setMouth(const Mouth& m) {
    this->mouth = m;
}

void Face::setOriginalFrame(const Mat& image) {
    this->originalFrame = image.clone();
//    this->normalize();
//    this->correctShadows();
}

Mat Face::getFaceImage() {
    if (this->area() <= 0)
        throw new string("Nenhuma face foi encontrada na figura.");
    
    Rect face(this->x, this->y, this->width, this->height);
    return this->originalFrame(face);
}

/**
 * Obtém uma imagem da região aproximada do olho, uma vez que estes já estejam definidos
 * @param whichEye  - qual dos olhos (direito/esquerdo)
 * @return 
 */
Mat Face::getEyeRegionImage(FaceObjType whichEye) {
    if (whichEye != VLGT_FACE_LEFT_EYE && whichEye != VLGT_FACE_RIGHT_EYE)
        throw new string("Tipo de objeto facial inválido para este método.");
    
    if ( (whichEye == VLGT_FACE_LEFT_EYE && this->leftEye->area() <= 0) ||
         (whichEye == VLGT_FACE_RIGHT_EYE && this->rightEye->area() <= 0) ) 
        return Mat();
    
    Point p = this->getAbsPos(whichEye);
    int w = ( whichEye == VLGT_FACE_LEFT_EYE ? this->leftEye->width : this->rightEye->width );
    int h = ( whichEye == VLGT_FACE_LEFT_EYE ? this->leftEye->height : this->rightEye->height );
    Rect eye( p.x, p.y, w, h );
    Mat img = this->originalFrame(eye);
//    // normaliza automaticamente a imagem
//    ImageUtils::normalizeAny( img, img );

//imshow("debug", img);
    return img;
}

Mat Face::getEyeRegionImage(Rect eyeRegion) {
    eyeRegion.x += this->x;
    eyeRegion.y += this->y;
    return this->originalFrame(eyeRegion);
}

Point Face::getAbsPos(FaceObjType type) {
    Point p;
    
    switch (type) {
        case VLGT_FACE_FACE:    // VLGT_FACE_FACE     
            p = Point(this->x, this->y);
            break;
        case VLGT_FACE_LEFT_EYE:    // VLGT_FACE_LEFT_EYE
            p = Point(this->x + this->leftEye->x, this->y + this->leftEye->y);
            break;
        case VLGT_FACE_RIGHT_EYE:    // VLGT_FACE_RIGHT_EYE 
            p = Point(this->x + this->rightEye->x, this->y + this->rightEye->y);
            break;
        case VLGT_FACE_MOUTH:    // VLGT_FACE_MOUTH 
            p = Point(this->x + this->mouth.x, this->y + this->mouth.y);
            break;
    }
    
    return p;
}

/**
 * Retorna a região de uma face, onde é provável que se encontre o olho esquerdo
 */
Rect Face::getLeftEyeEstimatedRegion() {
    return getEyeEstimatedRegion(VLGT_FACE_LEFT_EYE);
}

/**
 * Retorna a região de uma face, onde é provável que se encontre o olho direito
 */
Rect Face::getRightEyeEstimatedRegion() {
    return getEyeEstimatedRegion(VLGT_FACE_RIGHT_EYE);
}

/**
 * Retorna a região de uma face, onde é provável que se encontre um dos olhos
 * @param eyeType - qual dos olhos (esq/dir)
 * @return 
 */
Rect Face::getEyeEstimatedRegion(FaceObjType eyeType) {
    
    int x1,x2,y1,y2;
    
    if (eyeType == VLGT_FACE_RIGHT_EYE) {
        x1 = this->width/2;
        y1 = this->height/4;
        x2 = this->width - (this->width/6);
        y2 = this->height/2;
    } else {
        x1 = this->width/7;
        y1 = this->height/4;
        x2 = (this->width/2)*0.9;
        y2 = this->height/2;
    }
    
    Point pt1 = Point(x1, y1);
    Point pt2 = Point(x2, y2);
    
//    // ajusta o offset da face
//    pt1.x += this->x;
//    pt1.y += this->y;
//    pt2.x += this->x;
//    pt2.y += this->y;
     
//    rectangle(this->originalFrame, pt1, pt2, Scalar(0,255,0), 1, 1, 0);
   
    return Rect(pt1, pt2);
}

/**
 * Equaliza a imagem na região da face
 */
void Face::normalize() {
    if (this->area() > 0) {
        Rect r(this->x, this->y, this->width, this->height);
        Mat faceImg = this->originalFrame(r);
        ImageUtils::normalizeAny(faceImg, faceImg);
    }
}

/**
 * Corrige as sombras na face
 */
void Face::correctShadows() {
    if (this->area() > 0) {
        Rect r(this->x, this->y, this->width, this->height);
        Mat faceImg = this->originalFrame(r);
//imshow("antes", faceImg);
        ImageUtils::adjustVChannel(faceImg, faceImg);
//imshow("depois", faceImg);
    }
}

/**
 * Corrige brilho e contraste
 */
void Face::correctBrightness(double alpha, double beta) {
    if (this->area() > 0) {
        Rect r(this->x, this->y, this->width, this->height);
        Mat faceImg = this->originalFrame(r);
        ImageUtils::setContrastAndBrightness(faceImg, faceImg, alpha, beta);
    }
}

void Face::correctBrightness() {
    this->correctBrightness(2.0, 20.0);
}
