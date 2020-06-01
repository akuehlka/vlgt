/*
 * File:   newtestclass.h
 * Author: andrey
 *
 * Created on 11/03/2012, 20:42:46
 */

#ifndef NEWTESTCLASS_H
#define	NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testWebCam);
    CPPUNIT_TEST(testWebCam2);
    CPPUNIT_TEST(testNextFrame);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testWebCam();
    void testWebCam2();
    void testNextFrame();

};

#endif	/* NEWTESTCLASS_H */

