#include "runningaveragestream.h"

using namespace std;

RunningAverageStream::RunningAverageStream()
{
}

RunningAverageStream::RunningAverageStream(int size)
    : maxSampleSize(size)
{
}

double RunningAverageStream::getValue(double val)
{
    // deposita o valor na fila de amostras
    if (sample.size() >= maxSampleSize)
        sample.erase(sample.begin());
    sample.push_back(val);

    double tot = 0;
    // roda a média
    for (int i=0; i<sample.size(); i++) {
        tot += sample[i];
    }

    //retorna o valor
    return tot / sample.size();
}
