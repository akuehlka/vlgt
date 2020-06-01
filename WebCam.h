/* 
 * File:   WebCam.h
 * Author: andrey
 *
 * Created on 7 de Março de 2012, 11:18
 */

#ifndef WEBCAM_H
#define	WEBCAM_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class WebCam {
public:
    WebCam();
    WebCam(const WebCam& orig);
    virtual ~WebCam();
    cv::Mat nextFrame();
    void saveFrame(cv::Mat frame);
private:
    int camDeviceNr;
    float videoResWidth;
    float videoResHeight;
    
    cv::VideoCapture camera;
};

#endif	/* WEBCAM_H */

