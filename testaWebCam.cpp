/* 
 * File:   main.cpp
 * Author: andrey
 *
 * Created on 7 de Março de 2012, 11:44
 */

#include <cstdlib>
#include "WebCam.h"
#include <opencv2/highgui/highgui.hpp>

using namespace std;

/**
 * função para testar o objeto WebCam
 */
bool testaWebCam() {
    
    WebCam cam;
    
    bool stop(false);

    while (!stop) {
        cv::imshow("Teste WebCam", cam.nextFrame());
        
        // pressiona uma tecla para parar
        if (cv::waitKey(5) >= 'q')
            stop = true;
    }

    return true;
}