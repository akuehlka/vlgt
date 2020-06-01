/* 
 * File:   EyeDetector.cpp
 * Author: andrey
 * 
 * Created on 10 de Março de 2012, 09:38
 */

#include "EyeDetector.h"
#include "GenericDetector.h"

using namespace cv;

EyeCascadeDetector::EyeCascadeDetector(e_eye eye) : 
    GenericCascadeDetector( (eye == leftEye ? 
                        "/home/andrey/NetBeansProjects/vlgt/haarcascade_mcs_lefteye.xml" : 
                        "/home/andrey/NetBeansProjects/vlgt/haarcascade_mcs_righteye.xml") ),
    eyeDet(eye) {
}

EyeCascadeDetector::EyeCascadeDetector(const EyeCascadeDetector& orig) {
}

EyeCascadeDetector::~EyeCascadeDetector() {
}

/**
 * método público para obter o retângulo onde o olho foi encontrado na figura
 * @param       frame   Mat com a imagem (frame) onde procurar o olho
 * @return              Rect onde o olho foi encontrado
 */
Rect EyeCascadeDetector::getEyeRegion(const Mat& frame) {
    if (frame.rows == 0 || frame.cols == 0)
        return Rect();
    
    // como estou detectando um olho, somente a metade superior da figura interessa.
    // dependendo do olho, descarto o lado direito/esquerdo 
    Rect lq(0, 0, frame.rows/2, frame.cols/2);
    Rect rq(frame.cols/2, 0, frame.rows/2, frame.cols/2);
    Mat img;
    
    if (this->eyeDet == leftEye) {
        // detecto apenas no quadrante da esquerda
        img = frame(lq);
    } else {
        // detecto apenas no quadrante da direita
        img = frame(rq);
    }
    
    Rect retorno = getRegion(img);
    
    // para o caso da direita, tenho que normalizar a posição detectada
    if (this->eyeDet == rightEye) {
        retorno.x += frame.cols/2;
    }
    
    return retorno;
}

/**
 * método público para obter a imagem com o olho encontrado na figura
 * @param       frame   Mat com a imagem (frame) onde procurar o olho
 * @return              Mat com o olho
 */
Mat EyeCascadeDetector::getEyeImage(const Mat& frame) {
    return getImage(frame);
}