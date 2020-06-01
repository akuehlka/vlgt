/* 
 * File:   testaToGray.cpp
 * Author: andrey
 *
 * Created on 8 de Março de 2012, 11:44
 */

//#include <cstdlib>
#include "WebCam.h"
#include "ImageUtils.h"
#include <opencv2/highgui/highgui.hpp>

using namespace std;

/**
 * função para testar o método ToGrayScale
 */
bool testaToGray() {
    
    WebCam cam;
    
    int tipoConversao = 0;

    while ( tipoConversao < 4) {
        cv::imshow("Teste toGray", ImageUtils::toGrayScale( cam.nextFrame(),  tipoConversao ) );
        
        // pressiona uma tecla para parar
        if (cv::waitKey(5) >= 'q')
             tipoConversao++;
    }

    return true;
}