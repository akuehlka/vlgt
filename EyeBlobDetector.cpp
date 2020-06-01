/* 
 * File:   EyeBlobDetector.cpp
 * Author: andrey
 * 
 * Created on 23 de Março de 2012, 15:44
 */

#include "EyeBlobDetector.h"

using namespace std;
using namespace cv;

EyeBlobDetector::EyeBlobDetector():
   threshFactor(1)
{
}

EyeBlobDetector::EyeBlobDetector(const EyeBlobDetector& orig) {
}

EyeBlobDetector::~EyeBlobDetector() {
}

/**
 * Procura identificar em regiões específicas as características principais do olho
 * @param img            Mat com a imagem do olho
 * @param irisCenter     Point com o centro da iris já identificado.
 * @param drawBlob       bool informando se o blob deve ser desenhado na imagem original
 */
void EyeBlobDetector::findOuterScleraBlobs(const Mat& img, const RotatedRect& irisCenter, bool drawBlob=true) {
    // define uma região central com aprox. 30% da altura da imagem original
    int h = (img.rows/3)*1.6;
    int y = irisCenter.center.y - (h/2);
    
    int leftCornerX = MAX(irisCenter.boundingRect().x - irisCenter.boundingRect().width, 0);
    int rightCornerX = irisCenter.boundingRect().x + irisCenter.boundingRect().width/2;
    int rightCornerWidth = img.cols - rightCornerX;
    
    Rect narrowedEyeRectLeft(leftCornerX , y, img.cols/2, h);
    Rect narrowedEyeRectRight(rightCornerX, y, rightCornerWidth, h);
    
    try {
        Mat narrowedEyeLeft = img(narrowedEyeRectLeft);
        Mat narrowedEyeRight = img(narrowedEyeRectRight);
//        narrowedEyeLeft = ImageUtils::toGrayScale(narrowedEyeLeft, VLGT_IU_TOGRAY_GREEN);
//        equalizeHist(narrowedEyeLeft, narrowedEyeLeft);
//        
//        Point ptLeft = ImageUtils::eyeCornerProjection(narrowedEyeLeft);
//        // correção
//        ptLeft.x += leftCornerX;
//        ptLeft.y += y;
//        
//        if (drawBlob) {
//            Mat i = img;
//            circle(i, ptLeft, 3, Scalar(0,255,0), 1, 1, 0 );
//        }
        
        Mat i = ImageUtils::toBinaryHSV(narrowedEyeLeft);
        vector<vector<Point> > blobs = this->findBlobs(i);
        vector<Point> theBlobl = this->biggestBlob(blobs);
        
        i = ImageUtils::toBinaryHSV(narrowedEyeRight);
        blobs = this->findBlobs(i);
        vector<Point> theBlobr = this->biggestBlob(blobs);        
        
        if (drawBlob) {
            Point p(leftCornerX, y);
            this->drawBlob(img, theBlobl, p);
            
            p = Point(rightCornerX, y);
            this->drawBlob(img, theBlobr, p);
        }
    
    } catch (Exception e) {
        cerr << e.what() << endl;
    }
}

vector<Point> EyeBlobDetector::findEyeCorners(const Mat& img, Eye& eye, bool drawPoints) {
    // restringe a imagem ao olho, com base  na íris detectada
    Mat eyeImg = img; 
    Mat result;
    vector<Point> r;
    BlobDetector bd;
    
    if (eye.iris.center.x == 0 &&
            eye.iris.center.y == 0)
        return r;
        //TODO: throw new string("Íris não encontrada na imagem.");
    
    
    if (!img.empty()) {
        //defino uma janela de busca mais estreita com base no centro da íris
        Rect lmCorner; //= this->getEyeOuterCornerRegion(eye.iris, eye.eyeType, Size(img.rows,img.cols));

        Mat m = eyeImg(lmCorner);
imwrite("teste.png", m);
        m = ImageUtils::toBinaryHSV(m);
        
//imshow("findEyeCorners",m);
        result = ImageUtils::filterCorners3(m, threshFactor);
        vector<Point> blob = bd.biggestBlob( bd.findBlobs(result));
        
        // verifico a proporção (deve ser aprox. 2).
        double ratio = this->widthHeightProportion(blob);
        if (ratio >= 1.8 && ratio <= 2.2)
            cout << "Parece um olho." << endl;
        else {
            if (ratio < 1.8) {
                // incremento o fator de threshold
                threshFactor += 0.1;
            }
        }
        
        bd.drawBlob(m, blob, Point(0,0));

//        vector<Point> blob = bd.biggestBlob( bd.findBlobs(result));
//        bd.drawBlob(m, blob, Point(0,0));
//imshow("findEyeCorners",m);
        
//        Point p = bd.lowestPoint(bd.biggestBlob());
//        p.x += lmCorner.x;  // offset de x
//        p.y += lmCorner.y;  // offset de y
//        
//        if (eye.eyeType == VLGT_FACE_LEFT_EYE)
//            eye.leftMostCorner = p;
//        if (eye.eyeType == VLGT_FACE_RIGHT_EYE)
//            eye.rightMostCorner = p;
//        
//        if (drawPoints)
//                circle(eyeImg, p, 2, Scalar(0,255,0), 1, 1, 0);
//        
//        //defino uma janela de busca à direita com base no centro da íris
//        Rect rmCorner = this->getEyeInnerCornerRegion(eye.iris, eye.eyeType,  Size(eyeImg.cols, eyeImg.rows));
////rectangle(eyeImg, rmCorner, Scalar(255,0,0), 1, 1, 0);
//        result = ImageUtils::toBinaryEyeCorners(eyeImg(rmCorner));
//        p = bd.lowestPoint(bd.biggestBlob(bd.findBlobs(result)));
//        p.x += rmCorner.x;  //offset de x
//        p.y += rmCorner.y;  //offset de y
//
//        if (eye.eyeType == VLGT_FACE_LEFT_EYE)
//            eye.rightMostCorner = p;
//        if (eye.eyeType == VLGT_FACE_RIGHT_EYE)
//            eye.leftMostCorner = p;
//        
//        if (drawPoints)
//                circle(eyeImg, p, 2, Scalar(0,255,0), 1, 1, 0);
//        
    }
    
    return r;
}

/**
 * Calcula uma região reduzida para o olho, com base na íris detectada.
 * @param irisCenter
 * @param imgSize
 * @return 
 */
Rect EyeBlobDetector::getEyeRegion(const RotatedRect& irisCenter, const Size& imgSize) {
    int x, y, w, h;
    Rect cornerRegion;
    
    w = (imgSize.width/1.5);
    h = (imgSize.height/1.8);
    x = irisCenter.center.x - (w/2) ;
    y = irisCenter.center.y - (h/2);

    // proteção contra medidas erradas
    if (x < 0) 
        x = 0;
    if (y < 0)
        y = 0;
    if (x + w > imgSize.width)
        w = imgSize.width - x;
    if (y + h > imgSize.height)
        h = imgSize.height - y;

    cornerRegion = Rect(x, y, w, h);
    
    return cornerRegion;
}

Rect EyeBlobDetector::getEyeInnerCornerRegion(const RotatedRect& irisCenter, FaceObjType eye, const Size& imgSize) {
    if ( eye != VLGT_FACE_LEFT_EYE && eye != VLGT_FACE_RIGHT_EYE )
        throw string("O objeto esperado deve ser um olho, direito ou esquerdo.");

    int x, y, w, h;
    Rect cornerRegion;
    
    w = (imgSize.width/4);
    h = (imgSize.height/2);
    x = ( eye == VLGT_FACE_LEFT_EYE ? irisCenter.boundingRect().x + irisCenter.boundingRect().width : irisCenter.boundingRect().x - w );
    y = irisCenter.center.y + 5  - ((imgSize.height/2)/2);
    cornerRegion = Rect(x, y, w, h);

    return cornerRegion;
}