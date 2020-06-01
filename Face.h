/* 
 * File:   Face.h
 * Author: andrey
 *
 * Created on 19 de Março de 2012, 10:53
 */

#ifndef FACE_H
#define	FACE_H

#include <opencv2/core/core.hpp>
#include "Eye.h"
#include "Mouth.h"
#include "genericutils.h"

class Face: public cv::Rect {
public:
    Face();
    Face(cv::Rect faceRectangle);
    virtual ~Face();

    cv::Mat getFullFrame();
    void setLeftEye(Eye *e);
    Eye* getLeftEye();
    void setRightEye(Eye *e);
    Eye* getRightEye();
    void setMouth(const Mouth& m);
    void setOriginalFrame(const cv::Mat& image);
    cv::Mat getFaceImage();
    cv::Mat getEyeRegionImage(FaceObjType whichEye);
    cv::Mat getEyeRegionImage(cv::Rect eyeRegion);
    cv::Point getAbsPos(FaceObjType type);
    cv::Rect getLeftEyeEstimatedRegion();
    cv::Rect getRightEyeEstimatedRegion();
    void normalize();
    void correctShadows();
    void correctBrightness();
    void correctBrightness(double alpha, double beta);

    bool drawFace;
    bool drawEyes;
private:
    cv::Mat originalFrame; // frame original com a imagem onde foi encontrado uma face
    cv::Rect getEyeEstimatedRegion(FaceObjType eyeType);

    Eye *leftEye;
    Eye *rightEye;
    Mouth mouth;
};

#endif	/* FACE_H */

