#include "Estimator.h"

using namespace std;
using namespace cv;

Estimator::Estimator()
{
}

Estimator::Estimator(QString fileName, FixedReference fixRef, Size sz, int RAVGSize = 1) :
    porEstimator(new POREstimator(fileName)),
    rasX(RunningAverageStream(RAVGSize)),
    rasY(RunningAverageStream(RAVGSize)),
    frameCount(0),
    outputImage(Mat(2,2, CV_8UC3)),
    outputVideo(Mat(2,2, CV_8UC3)),
    video(new VideoFile(fileName.toStdString())),
    screenSize(sz),
    sectorHits(0),
    accumError(0),
    accumErrorDeg(0),
    accumErrorX(0),
    accumErrorY(0),
    accumErrorDegX(0),
    accumErrorDegY(0)
{
    porEstimator->setScreenSize( screenSize );
    estimatedCoordinates = porEstimator->processFile(fixRef, 1);
    VlgtDataUtils du;
    referenceCoordinates = du.loadScreenData(fileName);

    initSectors();
    initOutFile( fileName );
}

Estimator::~Estimator()
{
    delete porEstimator;
    delete video;

    // finaliza e fecha o arquivo de saída
    (*textOut) << "VLGT Estimator finishing at time " << QDateTime::currentDateTime().toString() << endl;
    outfile->close();
    delete outfile;
    delete textOut;

}

void Estimator::drawPOR()
{
//    qDebug("processando %d", frameCount);

    outputVideo = video->nextFrame();


//    // suavização dos valores estimados
    int theX = rasX.getValue( estimatedCoordinates.at(frameCount).x );
    int theY = rasY.getValue( estimatedCoordinates.at(frameCount).y );

    porPoint = Point( theX, theY );
    refPoint = Point( referenceCoordinates.at(frameCount).x,
                      referenceCoordinates.at(frameCount).y );

    qDebug("%d\t%d\t%d", frameCount, porPoint.x, porPoint.y);

    // calcula e acumula o erro em pixels e graus
    double errorPixels = sqrt( pow(double(porPoint.x) - double(refPoint.x), 2) + pow(double(porPoint.y) - double(refPoint.y), 2) );
    double errorPxX = sqrt( pow(double(porPoint.x) - double(refPoint.x), 2) );
    double errorPxY = sqrt( pow(double(porPoint.y) - double(refPoint.y), 2) );

    double subjectDistanceCm = 40; // assumo uma distância média de 40cm
    double circumference = (2*subjectDistanceCm)*CV_PI;
    double pixelsPerCm = 44.06;

    double errorCm = errorPixels/pixelsPerCm;
    double errorDegrees = (errorCm*360)/circumference;

    double errorCmX = errorPxX/pixelsPerCm;
    double errorDegreesX = (errorCmX*360)/circumference;
    double errorCmY = errorPxY/pixelsPerCm;
    double errorDegreesY = (errorCmY*360)/circumference;

    double totalFrameTime = estimatedCoordinates.at(frameCount).estimationTime +
            estimatedCoordinates.at(frameCount).detectionTime;

    accumError += errorPixels;
    accumErrorX += errorPxX;
    accumErrorY += errorPxY;
    accumErrorDeg += errorDegrees;
    accumErrorDegX += errorDegreesX;
    accumErrorDegY += errorDegreesY;
    accumTime += totalFrameTime;

    Mat s = Mat::zeros(screenSize, CV_8UC3);
    drawSectors(s, s);

    circle(s, refPoint, 30, Scalar(255,255,255), 2);  //  objeto referência
    circle(s, porPoint, 30, Scalar(255,255,255), -1); // estimativa

    // saída para o arquivo
    (*textOut) << frameCount                               << "," <<
               referenceCoordinates.at(frameCount).x    << "," <<
               referenceCoordinates.at(frameCount).y    << "," <<
               refSector                                << "," <<
               estimatedCoordinates.at(frameCount).x    << "," <<
               estimatedCoordinates.at(frameCount).y    << "," <<
//                  theX    << "," <<
//                  theY    << "," <<
               porSector                                << "," <<
               estimatedCoordinates.at(frameCount).estimationTime << endl;

    outputImage = s;
//    imshow("teste", outputImage);

    // contabiliza
    if (refSector == porSector)
        sectorHits++;

    // incrementa contador de frames
    frameCount++;
}

bool Estimator::hasFrames()
{
    return frameCount < estimatedCoordinates.size();
}

void Estimator::drawSectors(const Mat &src, Mat dst)
{
    int sectorCount = 0;
    for (int i=0; i<SECTOR_ROWS; i++)
        for (int j=0; j<SECTOR_COLS; j++)
        {
            rectangle(dst, sectors[i][j], Scalar(255,255,255), 2);

            // determina o setor do POR estimado
            if ( sectors[i][j].contains( porPoint ) ) {
                rectangle(dst, sectors[i][j], Scalar(100,100,100), -1);
                porSector = sectorCount;
            }
            // determina o setor do ponto de referência
            if ( sectors[i][j].contains( refPoint ) ) {
                refSector = sectorCount;
            }

            sectorCount++;
        }
}

void Estimator::initSectors()
{
    int srcw = screenSize.width;
    int srch = screenSize.height;
    int horSec = srcw / SECTOR_COLS;
    int verSec = srch / SECTOR_ROWS;

    for (int i=0; i<SECTOR_ROWS; i++)
        for (int j=0; j<SECTOR_COLS; j++)
        {
            Point p1( j*horSec, i*verSec );
            Point p2( (j+1)*horSec, (i+1)*verSec );
            sectors[i][j] = Rect(p1, p2);
        }
}

void Estimator::initOutFile(QString fileName)
{
    // arquivo de texto (saída)
    QString outFileName;
    QStringList tmplist = fileName.split(".");
    outFileName.append( tmplist[0] ).append(".estimation.txt");
    outfile = new QFile(outFileName);
    textOut = new QTextStream(outfile);
    // inicializo o arquivo para gravar os dados
    if (!outfile->open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug("Não foi possível abrir o arquivo de saída.");
    (*textOut) << "VLGT Estimator starting at time " << QDateTime::currentDateTime().toString() << endl;
    (*textOut) << "FrameCount"              << "," <<
          "ReferenceObjectX"        << "," <<
          "ReferenceObjectY"        << "," <<
          "ReferenceObjectSector"   << "," <<
          "EstimatedX"              << "," <<
          "EstimatedY"              << "," <<
          "EstimatedSector"         << "," <<
          "ProcessingTime" << endl;

}

// maior distância dentro da tela (para referência)
double Estimator::maxDist()
{
    return sqrt( pow(screenSize.width, 2) + pow(screenSize.height,  2) );
}
