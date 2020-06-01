/* 
 * File:   ImageUtils.h
 * Author: andrey
 *
 * Created on 8 de Março de 2012, 10:00
 */

#ifndef IMAGEUTILS_H
#define	IMAGEUTILS_H

#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define VLGT_IU_TOGRAY_SIMPLE 0
#define VLGT_IU_TOGRAY_RED    1
#define VLGT_IU_TOGRAY_GREEN  2
#define VLGT_IU_TOGRAY_BLUE   3

class ImageUtils {
public:
    ImageUtils();
    ImageUtils(const ImageUtils& orig);
    virtual ~ImageUtils();

    static cv::Mat toGrayScale(const cv::Mat& img, int type);
    static cv::Mat toBinaryHSV(const cv::Mat& img, int ht = 180, int st = 180, int vt = 57);
    static void findCorners(cv::Mat img);
    static cv::Mat filterCorners(const cv::Mat& img);
    static cv::Mat filterCorners2(const cv::Mat& img);
    static cv::Mat filterCorners3(const cv::Mat& img, double threshFactor);
    static std::vector<uchar> horizProjCorners(const cv::Mat& img);
    static cv::Mat toBinaryEyeCorners(const cv::Mat& img);
    static cv::Point eyeCornerProjection(const cv::Mat& img);
    static void normalizeAny(const cv::Mat& img, cv::Mat dst);
    static cv::Mat normalizeAndSmooth(const cv::Mat& img);
    static cv::Mat smooth(const cv::Mat& img);
    static double quadraticThreshold(const cv::Mat& img, double thFactor);
    static double cubicThreshold(const cv::Mat& img);
    static void setContrastAndBrightness(const cv::Mat& img, cv::Mat dst, double alpha, int beta);
    static void adjustVChannel(const cv::Mat& img, cv::Mat dst);
    static void imAdjust(cv::Mat img, cv::Mat dst, double loIn, double hiIn, double loOut, double hiOut);
    static void showHistogram(const cv::Mat& img);
    static void gammaCorrection(const cv::Mat& img, cv::Mat dst, double gamma);
    static void differenceOfGaussian(const cv::Mat& src, cv::Mat dst);
private:
    static int hProjection(const cv::Mat& src);
    static int vProjection(const cv::Mat& src);

};

#endif	/* IMAGEUTILS_H */

