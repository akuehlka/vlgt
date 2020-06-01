/*
 * File:   ImageUtilstestclass1.h
 * Author: andrey
 *
 * Created on 11/03/2012, 20:56:56
 */

#ifndef IMAGEUTILSTESTCLASS1_H
#define	IMAGEUTILSTESTCLASS1_H

#include <cppunit/extensions/HelperMacros.h>

class ImageUtilstestclass1 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ImageUtilstestclass1);

    CPPUNIT_TEST(testImageUtils);
    CPPUNIT_TEST(testToGrayScale);

    CPPUNIT_TEST_SUITE_END();

public:
    ImageUtilstestclass1();
    virtual ~ImageUtilstestclass1();
    void setUp();
    void tearDown();

private:
    void testImageUtils();
    void testToGrayScale();

};

#endif	/* IMAGEUTILSTESTCLASS1_H */

