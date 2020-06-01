/* 
 * File:   GenericDetector.cpp
 * Author: andrey
 * 
 * Created on 10 de Março de 2012, 11:10
 */

#include "GenericDetector.h"

GenericCascadeDetector::GenericCascadeDetector() {
}

GenericCascadeDetector::GenericCascadeDetector(std::string haarCascadeName) : cascadeName(haarCascadeName) {
}

GenericCascadeDetector::GenericCascadeDetector(const GenericCascadeDetector& orig) {
}

GenericCascadeDetector::~GenericCascadeDetector() {
}

/**
 * Método protegido que processa o frame, aplicando o cascade Classifier.
 * @param       frame   Mat com a imagem (frame) em grayscale a ser processado.
 * @return              Rect onde a face foi encontrada.
 */
Rect GenericCascadeDetector::processFrame(const Mat& frame) {
    if (cascade.empty()) {
        if (!cascadeName.empty()) {
            if (!cascade.load(cascadeName)) {
                throw std::string("Não foi possível carregar o arquivo de cascades.");
            }
        } else {
            throw std::string("Não foi especificado um arquivo cascades para carregar.");
        }
    }
    if (frame.channels() > 1) {
        throw std::string("Uma imagem com 1 canal era esperada.");
    }
    
    Mat frameEq;
    equalizeHist(frame, frameEq);
//    imshow("debug", frame);
    
    vector<Rect> vObjects;
    Size minSize( frame.rows/5, frame.cols/5 );
    this->cascade.detectMultiScale(frameEq, vObjects, 1.2, 3, 0|CV_HAAR_FIND_BIGGEST_OBJECT, minSize);
    
    if (vObjects.size() > 0) {
        return vObjects[0];
    } else
        return Rect();
}

/**
 * método protegido para obter o retângulo onde o objeto foi encontrado na figura
 * @param       frame   Mat com a imagem (frame) onde procurar o objeto
 * @return              Rect onde o objeto foi encontrado
 */
Rect GenericCascadeDetector::getRegion(const Mat& frame) {
    if (frame.cols == 0 || frame.rows == 0)
        return Rect();
    
    if (frame.channels() < 3){
        throw string("Uma imagem com 3 canais era esperada.");
    }
    
    Mat grayFrame = ImageUtils::toGrayScale(frame, VLGT_IU_TOGRAY_SIMPLE);
    
    return this->processFrame(grayFrame);
}

/**
 * método protegido para obter a imagem com o objeto encontrado na figura
 * @param       frame   Mat com a imagem (frame) onde procurar o objeto
 * @return              Mat com o objeto
 */
Mat GenericCascadeDetector::getImage(const Mat& frame) {
    if (frame.channels() < 3){
        throw string("Uma imagem com 3 canais era esperada.");
    }
    
    Mat grayFrame = ImageUtils::toGrayScale(frame, VLGT_IU_TOGRAY_SIMPLE);
    
    Rect rObject = this->processFrame(grayFrame);
    if (rObject.size().height > 0 && rObject.size().width > 0)
        return frame(rObject);
    
    return Mat::zeros(Size(0,0), CV_8UC1);
}