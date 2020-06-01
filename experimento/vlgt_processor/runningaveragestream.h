#ifndef RUNNINGAVERAGESTREAM_H
#define RUNNINGAVERAGESTREAM_H

#include <vector>

class RunningAverageStream
{
public:
    RunningAverageStream();
    RunningAverageStream(int size);
    double getValue(double val);
private:
    int maxSampleSize;
    std::vector<double> sample;
};

#endif // RUNNINGAVERAGESTREAM_H
