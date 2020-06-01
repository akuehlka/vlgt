/* 
 * File:   PointRunningAverageStream.cpp
 * Author: andrey
 * 
 * Created on 21 de Novembro de 2012, 20:34
 */

#include <vector>
#include <opencv2/core/core.hpp>

#include "PointRunningAverageStream.h"

using namespace cv;
using namespace std;

PointRunningAverageStream::PointRunningAverageStream() {
}

PointRunningAverageStream::PointRunningAverageStream(const PointRunningAverageStream& orig) {
}

PointRunningAverageStream::PointRunningAverageStream(int size) 
        : maxSampleSize(size),
        smoothX(false),
        smoothY(true)
{
}

PointRunningAverageStream::~PointRunningAverageStream() {
}

/**
 * Obtém uma média dos últimos maxSampleSize Pontos
 * @param pt
 * @return 
 */
Point PointRunningAverageStream::getPoint(cv::Point pt) {
    // deposita o valor na fila de amostras
    if (sampleQueue.size() >= maxSampleSize)
        sampleQueue.erase(sampleQueue.begin());
    sampleQueue.push_back(pt);

    double totx = 0;
    double toty = 0;
    // roda a média
    for (int i=0; i<sampleQueue.size(); i++) {
//        if (smoothX) 
            totx += sampleQueue.at(i).x;
//        if (smoothY)
            toty += sampleQueue.at(i).y;
    }
    
    // calcula a média 
    Point res( totx/sampleQueue.size(), toty/sampleQueue.size() );
//    Point res( 
//        ( smoothX ? totx/sampleQueue.size() : pt.x ), 
//        ( smoothY ? toty/sampleQueue.size() : pt.y )
//    );

    //retorna o valor
    return res;
}