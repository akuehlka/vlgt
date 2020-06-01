/* 
 * File:   VideoFile.cpp
 * Author: andrey
 * 
 * Created on 25 de Março de 2012, 11:11
 */

#include <opencv2/highgui/highgui.hpp>

#include "VideoFile.h"

using namespace std;
using namespace cv;

VideoFile::VideoFile() {
}

VideoFile::VideoFile(std::string name) {
    this->file = new VideoCapture();
    file->open(name);
    
    if (!file->isOpened())
        throw new string("Um erro ocorreu abrindo o vídeo.");
}

VideoFile::VideoFile(const VideoFile& orig) {
}

VideoFile::~VideoFile() {
    delete file;
}

Mat VideoFile::nextFrame() {
    Mat frame;
    *file >> frame;
    return frame;
}
