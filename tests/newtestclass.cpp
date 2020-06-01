/*
 * File:   newtestclass.cpp
 * Author: andrey
 *
 * Created on 11/03/2012, 20:42:46
 */

#include "newtestclass.h"
#include "WebCam.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testWebCam() {
    WebCam webCam();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(true);
    }
}

void newtestclass::testWebCam2() {
//    const WebCam& orig;
//    WebCam webCam(orig);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(true);
    }
}

void newtestclass::testNextFrame() {
    WebCam webCam;
    cv::Mat result = webCam.nextFrame();
    if (result.empty()) {
        CPPUNIT_ASSERT(false);
    }
}

