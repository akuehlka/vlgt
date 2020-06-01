/* 
 * File:   BlobDetector.h
 * Author: andrey
 *
 * Created on 15 de Março de 2012, 08:58
 */

#ifndef BLOBDETECTOR_H
#define	BLOBDETECTOR_H

#include "BlobDetector.h"

class BlobDetector {
public:
    BlobDetector();
    BlobDetector(const BlobDetector& orig);
    virtual ~BlobDetector();
    
    std::vector<cv::Point> biggestBlob(const std::vector<std::vector<cv::Point> >& blobsList);
    cv::Point rightMostBlob(const std::vector<std::vector<cv::Point> >& blobsList);
    void drawBlob(cv::Mat img, const std::vector<cv::Point>& blob, const cv::Point& offset);
    double compareBlobs(const std::vector<cv::Point>& aBlob, const std::vector<cv::Point>& anotherBlob);
    std::vector<std::vector<cv::Point> > findBlobs(const cv::Mat& img);
    cv::Point lowestPoint(const std::vector<cv::Point>& contours);
    double widthHeightProportion(const std::vector<cv::Point>& blob);
    cv::Point leftMost(const std::vector<cv::Point>& contours);
    cv::Point rightMost(const std::vector<cv::Point>& contours);
private:

};

#endif	/* BLOBDETECTOR_H */

