/* 
 * File:   VideoFile.h
 * Author: andrey
 *
 * Created on 25 de Março de 2012, 11:11
 */

#ifndef VIDEOFILE_H
#define	VIDEOFILE_H

#include <string>

class VideoFile {
public:
    VideoFile();
    VideoFile(std::string name);
    VideoFile(const VideoFile& orig);
    virtual ~VideoFile();
    
    cv::Mat nextFrame();
private:
    cv::VideoCapture *file;
};

#endif	/* VIDEOFILE_H */

