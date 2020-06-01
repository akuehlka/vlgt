/*
 * File:   GenericDetectorTest1.cpp
 * Author: andrey
 *
 * Created on 12/03/2012, 15:55:48
 */

#include "GenericDetectorTest1.h"
#include "GenericDetector.h"


CPPUNIT_TEST_SUITE_REGISTRATION(GenericDetectorTest1);

GenericDetectorTest1::GenericDetectorTest1() {
}

GenericDetectorTest1::~GenericDetectorTest1() {
}

void GenericDetectorTest1::setUp() {
}

void GenericDetectorTest1::tearDown() {
}

void GenericDetectorTest1::testGenericDetector() {
    GenericCascadeDetector genericDetector();
    if ( false ) {
        CPPUNIT_ASSERT(false);
    }
}

void GenericDetectorTest1::testGenericDetector2() {
    std::string haarCascadeName;
    GenericCascadeDetector genericDetector(haarCascadeName);
    if ( false ) {
        CPPUNIT_ASSERT(false);
    }
}

