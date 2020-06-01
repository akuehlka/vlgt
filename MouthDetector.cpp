/* 
 * File:   MouthDetector.cpp
 * Author: andrey
 * 
 * Created on 18 de Março de 2012, 15:17
 */

#include "MouthDetector.h"

MouthDetector::MouthDetector() : GenericCascadeDetector("haarcascade_mcs_mouth.xml") {
}

MouthDetector::MouthDetector(const MouthDetector& orig) {
}

MouthDetector::~MouthDetector() {
}

/**
 * método público para obter o retângulo onde a boca foi encontrada na figura
 * @param       frame   Mat com a imagem (frame) onde procurar a boca
 * @return              Rect onde a boca foi encontrada
 */
Rect MouthDetector::getMouthRegion(const cv::Mat& frame) {
    // como estou detectando a boca, somente o centro inferior da figura interessa.
    Rect ciq(frame.cols/4, frame.rows/2, frame.rows/2, frame.cols/2);
    Mat img;
    
    // detecto apenas no quadrante centro-inferior da face
    img = frame(ciq);

//if (img.rows > 0 && img.cols > 0) imshow("Debug", img);
    Rect retorno = getRegion(img);
    
    // Tenho que retornar a posição absoluta em relação à face
    retorno.x += frame.cols/4;
    retorno.y += frame.rows/2;
    
    return retorno;
}

/**
 * método público para obter a imagem com o nariz que foi encontrado na figura
 * @param       frame   Mat com a imagem (frame) onde procurar o nariz
 * @return              Mat com o nariz
 */
Mat MouthDetector::getMouthImage(const cv::Mat& frame) {
    return getImage(frame);
}