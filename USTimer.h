/* 
 * File:   MSClock.h
 * Author: andrey
 *
 * Created on 25 de Abril de 2011, 17:09
 */

#ifndef _USTIMER_H
#define	_USTIMER_H

#include <string>

class USTimer {
public:
    USTimer();
    virtual ~USTimer();

    double getDiffSeconds();
    double getDiffMSeconds();
    std::string getDiffSecondsStr();
    std::string getDiffMSecondsStr();
private:
    double sstart, send, freq;
    void startTimer();
    void stopTimer();
};

#endif	/* _USTIMER_H */

