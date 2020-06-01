#include "irisfinderwrapper.h"

IrisFinderWrapper::IrisFinderWrapper(QObject *parent) :
    QObject(parent)
{
}

void IrisFinderWrapper::setIrisBrightnessAlpha(int value)
{
    this->irisBrightnessAlpha = value/10;
}

void IrisFinderWrapper::setIrisBrightnessBeta(int value)
{
    this->irisBrightnessBeta = value;
}
