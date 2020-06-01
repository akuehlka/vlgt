/*
 * File:   GenericDetectorTest1.h
 * Author: andrey
 *
 * Created on 12/03/2012, 15:55:47
 */

#ifndef GENERICDETECTORTEST1_H
#define	GENERICDETECTORTEST1_H

#include <cppunit/extensions/HelperMacros.h>

class GenericDetectorTest1 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(GenericDetectorTest1);

    CPPUNIT_TEST(testGenericDetector);
    CPPUNIT_TEST(testGenericDetector2);

    CPPUNIT_TEST_SUITE_END();

public:
    GenericDetectorTest1();
    virtual ~GenericDetectorTest1();
    void setUp();
    void tearDown();

private:
    void testGenericDetector();
    void testGenericDetector2();

};

#endif	/* GENERICDETECTORTEST1_H */

