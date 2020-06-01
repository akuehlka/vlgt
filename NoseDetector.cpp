/* 
 * File:   NoseDetector.cpp
 * Author: andrey
 * 
 * Created on 17 de Março de 2012, 14:34
 */

#include "NoseDetector.h"

using namespace cv;
using namespace std;

NoseDetector::NoseDetector() : GenericCascadeDetector("haarcascade_mcs_nose.xml")  {
}

NoseDetector::NoseDetector(const NoseDetector& orig) {
}

NoseDetector::~NoseDetector() {
}

/**
 * método público para obter o retângulo onde o nariz foi encontrado na figura
 * @param       frame   Mat com a imagem (frame) onde procurar o nariz
 * @return              Rect onde o nariz foi encontrado
 */
Rect NoseDetector::getNoseRegion(const cv::Mat& frame) {
    // como estou detectando o nariz, somente o centro da figura interessa.
    Rect cq(frame.rows/4, frame.cols/4, frame.rows/2, frame.cols/2);
    Mat img;
    
    // detecto apenas no quadrante central da face
    img = frame(cq);

    Rect retorno = getRegion(img);
    
    // Tenho que retornar a posição absoluta em relação à face
    retorno.x += frame.cols/4;
    retorno.y += frame.rows/4;
    
    return retorno;
}

/**
 * método público para obter a imagem com o nariz que foi encontrado na figura
 * @param       frame   Mat com a imagem (frame) onde procurar o nariz
 * @return              Mat com o nariz
 */
Mat NoseDetector::getNoseImage(const cv::Mat& frame) {
    return getImage(frame);
}