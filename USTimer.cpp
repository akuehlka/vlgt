/* 
 * File:   MSClock.cpp
 * Author: andrey
 * 
 * Created on 25 de Abril de 2011, 17:09
 */

#include <iostream>
#include <cstdio>
#include <opencv2/core/core.hpp>
#include "USTimer.h"

using namespace cv;

USTimer::USTimer() {
    this->startTimer();
    this->freq = getTickFrequency();
}

USTimer::~USTimer() {
}

void USTimer::startTimer()
{
    this->sstart = (double)getTickCount();
}

void USTimer::stopTimer()
{
    this->send = (double)getTickCount();
}

double USTimer::getDiffSeconds()
{
    this->stopTimer();
    // diferença de tempo em ticks / (frequência * 1000)
    return (this->send - this->sstart)/this->freq;
}

double USTimer::getDiffMSeconds()
{
    this->stopTimer();
    // diferença de tempo em ticks / (frequência * 1000)
    return ((this->send - this->sstart)/(this->freq)*1000.);
}

std::string USTimer::getDiffMSecondsStr()
{
    char buffer[50];
    std::string str;
    int n = sprintf(buffer, "%f", this->getDiffMSeconds());
    str.append(buffer);
    return str;
}

std::string USTimer::getDiffSecondsStr()
{
    char buffer[50];
    std::string str;
    int n = sprintf(buffer, "%f", this->getDiffSeconds());
    str.append(buffer);
    return str;
}