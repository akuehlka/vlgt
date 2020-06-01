/* 
 * File:   BlobDetector.cpp
 * Author: andrey
 * 
 * Created on 15 de Março de 2012, 08:58
 */

#include <opencv2/highgui/highgui.hpp>

#include "BlobDetector.h"
#include "ImageUtils.h"

using namespace std;
using namespace cv;

BlobDetector::BlobDetector() {
}

BlobDetector::BlobDetector(const BlobDetector& orig) {
}

BlobDetector::~BlobDetector() {
}

/**
 * Encontra blobs em uma imagem binarizada.
 * @param img   Mat com a imagem binarizada onde será realizada a detecção.
 * @return      vector<vector<Point> > com os contornos dos blobs encontrados.
 */
vector<vector<Point> > BlobDetector::findBlobs(const Mat& img) {
    if (img.channels() > 1)
        throw new string("Uma imagem binarizada era esperada.");
    
    vector<vector<Point> > blobsFound;
    Mat imgTemp(img);
    // detecto somente os contornos externos
    findContours( imgTemp, blobsFound, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point() );
    
    /// Encontra o contorno (convex Hull) para cada conjunto de pontos
    vector<vector<Point> > hulls( blobsFound.size() );
    for( int i = 0; i < blobsFound.size(); i++ ) {
        vector<Point> tmp;
        convexHull( Mat(blobsFound[i]), tmp, false ); 
        hulls[i] = tmp;
    }
    
    return hulls;
}

/**
 * Encontra blobs em uma imagem e retorna o maior deles.
 * @param vector<vector<Point> >           Lista de blobs
 * @return              Blob com o maior blob encontrado.
 */
vector<Point> BlobDetector::biggestBlob(const vector<vector<Point> >& blobsList) {

    vector<Point> theBlob;
    for (int i=0; i < blobsList.size(); i++ ) {
        vector<Point> tmpBlob(blobsList[i]);
        if (this->compareBlobs(tmpBlob, theBlob) > 0) {
            theBlob = tmpBlob;
        }
    }
    
    return theBlob;
}

/**
 * Em um conjunto de contornos detectados, encontra o blob que se situa mais à direita.
 * @param blobsList
 * @return 
 */
Point BlobDetector::rightMostBlob(const vector<vector<Point> >& blobsList) {
    Point rm(0,0);
    
    for ( int i=0; i < blobsList.size(); i++ ) {

        vector<Point> aBlob = blobsList[i];

        /// Get the moments
        Moments mu;
        mu = moments(aBlob, false);

        ///  Get the mass center:
        Point2f mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
        
        if (mc.x > rm.x)
            rm = mc;
    }
    
    return rm;
}

/**
 * Desenha o blob na imagem
 * @param img   Mat imagem onde desenhar
 * @param blob  Blob a ser desenhado
 */
void BlobDetector::drawBlob(cv::Mat img, const vector<Point>& blob, const Point& offset) {
    Scalar color = Scalar( 255, 255, 255 );
    vector<vector<Point> > arrayOfArrays;
    arrayOfArrays.push_back(blob);
    drawContours( img, arrayOfArrays, -1, color, 1, 8, vector<Vec4i>(), 0, offset );
}

/**
 * Compara dois "blobs" através de sua área
 * @param aBlob         vector<Point> contorno do primeiro blob
 * @param anotherBlob   vector<Point> contorno do segundo blob
 * @return              double diferença entre a área dos dois blobs
 */
double BlobDetector::compareBlobs(const vector<Point>& aBlob, const vector<Point>& anotherBlob) {
    double area, anotherArea;
    
    area = (aBlob.size() == 0 ? 0 : contourArea(aBlob));
    anotherArea = (anotherBlob.size() == 0 ? -9999999. : contourArea(anotherBlob));
    
    return area - anotherArea;
}

/**
 * Calcula a proporção entre largura x altura de um blob
 * @param blob
 * @return 
 */
double BlobDetector::widthHeightProportion(const vector<Point>& blob) {
    Rect r = boundingRect(Mat(blob));
    if (r.area() == 0) return 0;
    
    return r.width / r.height;
}


/**
 * Retorna a posição onde se encontra o ponto mais abaixo em um blob
 */
Point BlobDetector::lowestPoint(const vector<Point>& contours) {
    Point lower(0, 0);
    for (int i = 0; i < contours.size(); i++) {
        if ( ((Point)contours[i]).y > lower.y ) 
            lower = (Point)contours[i];
    }
    
    return lower;
}

/**
 * Em uma imagem que contém contornos detectados, encontra o ponto mais à 
 * esquerda
 * @param contours
 * @return 
 */
Point BlobDetector::leftMost(const vector<Point>& contours) {
    int minx = 999999;
    int maxy = 0;
    for (int i=0; i<contours.size(); i++) {
        if (contours[i].x < minx)
            minx = contours[i].x;
    }
    for (int i=0; i<contours.size(); i++) {
        if (contours[i].x == minx) {
            if (contours[i].y > maxy)
                maxy = contours[i].y;
        }
    }    
    
    return Point(minx,maxy);
}

/**
 * Em uma imagem que contém contornos detectados, encontra o ponto mais à 
 * direita
 * @param contours
 * @return 
 */
Point BlobDetector::rightMost(const vector<Point>& contours) {
    int maxx = 0;
    int maxy = 0;
    for (int i=0; i<contours.size(); i++) {
        if (contours[i].x > maxx)
            maxx = contours[i].x;
    }
    for (int i=0; i<contours.size(); i++) {
        if (contours[i].x == maxx) {
            if (contours[i].y > maxy)
                maxy = contours[i].y;
        }
    }    
    
    return Point(maxx,maxy);
}

