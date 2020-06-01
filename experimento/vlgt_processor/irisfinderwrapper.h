#ifndef IRISFINDERWRAPPER_H
#define IRISFINDERWRAPPER_H

#include <QObject>
#include "../../IrisFinder.h"

class IrisFinderWrapper : public QObject, public IrisFinder
{
    Q_OBJECT
public:
    explicit IrisFinderWrapper(QObject *parent = 0);
    
signals:
    
public slots:
    void setIrisBrightnessAlpha(int value);
    void setIrisBrightnessBeta(int value);

};

#endif // IRISFINDERWRAPPER_H
