/* 
 * File:   WebCam.cpp
 * Author: andrey
 * 
 * Created on 7 de Março de 2012, 11:18
 */

#include "WebCam.h"

using namespace std;
using namespace cv;

/**
 * Construtor padrão para o objeto WebCam
 */
WebCam::WebCam() {
    this->camDeviceNr    = 0;
    this->videoResWidth  = 640.0;
    this->videoResHeight = 480.0;
    
    this->camera = VideoCapture(this->camDeviceNr);
    
    this->camera.set(CV_CAP_PROP_FRAME_WIDTH, videoResWidth);
    this->camera.set(CV_CAP_PROP_FRAME_HEIGHT, videoResHeight);
//    this->camera.set(CV_CAP_PROP_BRIGHTNESS, 0.0);
//    this->camera.set(CV_CAP_PROP_CONTRAST, 0.0);
//    this->camera.set(CV_CAP_PROP_GAIN, 0.0);

    
    // verifica se realmente abriu
    if (!this->camera.isOpened()) {
        // TODO: tratar isso com exceção
        cerr << "Erro abrindo a captura da camera " << this->camDeviceNr << "." << endl;
    }
}

WebCam::WebCam(const WebCam& orig) {
}

/**
 * Destrutor padrão para a classe WebCam
 */
WebCam::~WebCam() {
    this->camera.release();
}

/**
 * Método que obtém da câmera o próximo frame
 * @return cv::Mat
 */
Mat WebCam::nextFrame() {
    Mat frame;
    this->camera.read(frame);
    return frame;
}

void WebCam::saveFrame(Mat frame) {
    cv::imwrite("file0001.jpg", frame);    
}