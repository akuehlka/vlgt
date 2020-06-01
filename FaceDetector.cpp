/* 
 * File:   FaceDetector.cpp
 * Author: andrey
 * 
 * Created on 7 de Março de 2012, 18:21
 */

#include <string>
#include "FaceDetector.h"

using namespace std;
using namespace cv;

FaceDetector::FaceDetector() : GenericCascadeDetector("/home/andrey/NetBeansProjects/vlgt/haarcascade_frontalface_default.xml") {
}

FaceDetector::FaceDetector(const FaceDetector& orig) {
}

FaceDetector::~FaceDetector() {
}

/**
 * método público para obter o retângulo onde a face foi encontrada na figura
 * @param       frame   Mat com a imagem (frame) onde procurar a face
 * @return              Rect onde a face foi encontrada
 */
Rect FaceDetector::getFaceRegion(const cv::Mat& frame) {
    return getRegion(frame);
}

/**
 * método público para obter a imagem com a face foi encontrada na figura
 * @param       frame   Mat com a imagem (frame) onde procurar a face
 * @return              Mat com a face
 */
Mat FaceDetector::getFaceImage(const cv::Mat& frame) {
    return getImage(frame);
}