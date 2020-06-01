/*
 * File:   ImageUtilstestclass1.cpp
 * Author: andrey
 *
 * Created on 11/03/2012, 20:56:56
 */

#include <opencv2/highgui/highgui.hpp>

#include "ImageUtilstestclass1.h"
#include "ImageUtils.h"
#include "WebCam.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ImageUtilstestclass1);

ImageUtilstestclass1::ImageUtilstestclass1() {
}

ImageUtilstestclass1::~ImageUtilstestclass1() {
}

void ImageUtilstestclass1::setUp() {
}

void ImageUtilstestclass1::tearDown() {
}

void ImageUtilstestclass1::testImageUtils() {
    ImageUtils imageUtils();
    if ( imageUtils == 0 ) {
        CPPUNIT_ASSERT(false);
    }
}

void ImageUtilstestclass1::testToGrayScale() {
    WebCam cam;
    cv::Mat img = cam.nextFrame();

    ImageUtils imageUtils;
    cv::Mat result = imageUtils.toGrayScale(img, VLGT_IU_TOGRAY_SIMPLE);
    if (result.channels() > 1) {
        CPPUNIT_ASSERT(false);
    }

    result = imageUtils.toGrayScale(img, VLGT_IU_TOGRAY_RED);
    if (result.channels() > 1) {
        CPPUNIT_ASSERT(false);
    }
    
    result = imageUtils.toGrayScale(img, VLGT_IU_TOGRAY_GREEN);
    if (result.channels() > 1) {
        CPPUNIT_ASSERT(false);
    }
    
    result = imageUtils.toGrayScale(img, VLGT_IU_TOGRAY_BLUE);
    if (result.channels() > 1) {
        CPPUNIT_ASSERT(false);
    }


}

