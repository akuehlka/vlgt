/* 
 * File:   FileProcessor.h
 * Author: andrey
 *
 * Created on 14 de Junho de 2012, 20:38
 */

#ifndef FILEPROCESSOR_H
#define	FILEPROCESSOR_H

#include <vector>
#include <string>

class FileProcessor {
public:
    FileProcessor();
    FileProcessor(const FileProcessor& orig);
    virtual ~FileProcessor();
    
    void setFileList(const std::vector<std::string>& newList);
    void processFile(const std::string inFileName);
    
private:
    std::vector<std::string> fileList;
    std::string outFileName;

};

#endif	/* FILEPROCESSOR_H */

