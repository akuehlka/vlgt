/* 
 * File:   EyeBlobDetector.h
 * Author: andrey
 *
 * Created on 23 de Março de 2012, 15:44
 */

#ifndef EYEBLOBDETECTOR_H
#define	EYEBLOBDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "BlobDetector.h"
#include "ImageUtils.h"
#include "Face.h"

class EyeBlobDetector: public BlobDetector {
public:
    EyeBlobDetector();
    EyeBlobDetector(const EyeBlobDetector& orig);
    virtual ~EyeBlobDetector();

    void findOuterScleraBlobs(const cv::Mat& img, const cv::RotatedRect& irisCenter, bool drawBlob);
    std::vector<cv::Point> findEyeCorners(const cv::Mat& img, Eye& eye, bool drawPoints);

    cv::Rect narrowedEye;
private:
    double threshFactor;
    
    cv::Rect getEyeRegion(const cv::RotatedRect& irisCenter, const cv::Size& imgSize);
    cv::Rect getEyeOuterCornerRegion(const cv::RotatedRect& irisCenter, FaceObjType eye, const cv::Size& imgSize);
    cv::Rect getEyeInnerCornerRegion(const cv::RotatedRect& irisCenter, FaceObjType eye, const cv::Size& imgSize);
};

#endif	/* EYEBLOBDETECTOR_H */

