#include "vlgtprocessor.h"

using namespace std;
using namespace cv;

VlgtProcessor::VlgtProcessor()
{
    Mat i(2,2, CV_8UC3);
    outputImage = i;
    outputEye = i;
}

VlgtProcessor::VlgtProcessor(QString path, int rasSize):
    filePath(path),
    rasQueueSize(rasSize)
{
}

VlgtProcessor::~VlgtProcessor()
{
}

void VlgtProcessor::process(QString fileName) {

    try {
        // detectores utilizados
        FaceDetector fd;
        EyeProcessor eproc;

        // arquivo de vídeo (entrada)
        QString inFile = filePath;
        inFile.append("/").append( fileName );
        VideoFile videoFile = VideoFile( inFile.toStdString() );

        // arquivo de texto (saída)
        QString outFileName = filePath;
        QStringList tmplist = fileName.split(".");
        outFileName.append("/").append( tmplist.at(0) ).append(".result.txt");
//        qDebug(outFileName.toStdString().c_str());
        QFile outfile(outFileName);
        QTextStream ts(&outfile);
        // inicializo o arquivo para gravar os dados
        if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
            qDebug("Não foi possível abrir o arquivo de saída.");
        ts << "VLGT Processor starting at time " << QDateTime::currentDateTime().toString() << endl;
        ts << "FrameCount"      << "," <<
              "LEyeROIX"        << "," <<
              "LEyeROIY"        << "," <<
              "LEyeROIW"        << "," <<
              "LEyeROIH"        << "," <<
              "LIrisX"          << "," <<
              "LIrisY"          << "," <<
              "LInnerCornerX"   << "," <<
              "LInnerCornerY"   << "," <<
              "LOuterCornerX"   << "," <<
              "LOuterCornerY"   << "," <<
              "REyeROIX"        << "," <<
              "REyeROIY"        << "," <<
              "REyeROIW"        << "," <<
              "REyeROIH"        << "," <<
              "RIrisX"          << "," <<
              "RIrisY"          << "," <<
              "LInnerCornerX"   << "," <<
              "LInnerCornerY"   << "," <<
              "LOuterCornerX"   << "," <<
              "LOuterCornerY"   << "," <<
              "FrameTimeS"     << endl;

        stop = false;
        int frameCount = 0;

        // enquanto tiverem frames no vídeo ou não for interrompido,
        while (!stop) {
            double t = (double)getTickCount();

            Mat f = videoFile.nextFrame();
            if (f.empty())
                break;

            frameCount++;            // registra a contagem de frames

            try {
                Face face = fd.getFaceRegion(f);
                if (face.area() == 0) continue;

                face.setOriginalFrame(f); // para uso posterior, anexo a imagem
                face.correctBrightness( this->faceBrightnessAlpha, this->faceBrightnessBeta );

                Eye lEye;
                Eye rEye;
                // se uma face foi encontrada
                if (!face.area() <= 0) {

                    // localização do olho/íris esquerdos
                    lEye = Eye( face.getLeftEyeEstimatedRegion(), VLGT_FACE_LEFT_EYE );
                    lEye.ifinder = &ifind;
                    lEye.findIris( face.getEyeRegionImage( lEye ) );
                    face.setLeftEye( &lEye );

                    // abandonada, uma vez que a utilização do canto da janela
                    // é mais confiável, e relativamente estável.
//                    eproc.newLocateCorners( face );

                    // localização do olho/íris direitos
                    // TODO

//                    imshow("debug", face.getFullFrame());
                    Mat img = face.getFullFrame();
                    this->outputImage = img.clone();
                    Mat olho = face.getEyeRegionImage( lEye );
                    this->outputEye = olho.clone();
                }

                // calcula o tempo
                double ft = ((double)getTickCount() - t) / getTickFrequency();

                ts << frameCount << ",";
                // saída para o arquivo (OE)
                ts << face.getLeftEye()->x << "," <<
                      face.getLeftEye()->y << "," <<
                      face.getLeftEye()->width << "," <<
                      face.getLeftEye()->height << ",";  // ROI do olho esquerdo

                int ix = face.getLeftEye()->x + face.getLeftEye()->iris.center.x;
                // como tentativa de reforçar o pequeno deslocamento no eixo Y,
                // vou tentar diminuir desta medida a altura da íris
//                int iy = face.getLeftEye()->y + (face.getLeftEye()->iris.center.y - face.getLeftEye()->iris.boundingRect().height);
                int iy = face.getLeftEye()->y + face.getLeftEye()->iris.center.y;
                iy = MAX(0, iy);

                ts << ix << "," <<
                      iy << ",";                     // posição da íris esquerda
                ts << 0 << "," << 0 << ",";               // canto esquerdo
                ts << 0 << "," << 0 << ",";             // canto direito

                // saída para o arquivo (OD)
                ts << 0 << "," << 0 << "," << 0 << "," << 0 << ",";  // ROI do olho direito
                ts << 0 << "," << 0 << ",";                     // posição da íris direita
                ts << 0 << "," << 0 << ",";               // canto esquerdo
                ts << 0 << "," << 0 << ",";            // canto direito
                ts << ft << endl; // tempo

            } catch (cv::Exception cvEx) {
                qDebug("Excecao do OpenCV.");
            }


            // pressiona uma tecla para parar
            if (waitKey(1) >= 'q')
                stop = true;

        }

        ts << "VLGT Processor finishing at time " << QDateTime::currentDateTime().toString() << endl;
        outfile.close();

    } catch (string ex) {
        qDebug( ex.c_str() );
    }
}

void VlgtProcessor::processQueue(QStringList fileList) {
    QStringListIterator it(fileList);

    while (it.hasNext() && !stop) {
        process(it.next());
    }
    this->stop = false;
}


void VlgtProcessor::setFaceBrightnessAlpha(int value) {
    faceBrightnessAlpha = (double)value/10;
}

void VlgtProcessor::setFaceBrightnessBeta(int value) {
    faceBrightnessBeta = (double)value;
}

void VlgtProcessor::setStop(bool value)
{
    stop = value;
}

void VlgtProcessor::setRasQueueSize(int value)
{
    rasQueueSize = value;
}
