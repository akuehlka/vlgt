#include "capture.h"
#include "widget.h"
#include "ui_widget.h"
#include <QTextStream>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

Capture::Capture(QWidget *parent) :
    QWidget(parent)
{
    camera = VideoCapture(0);  // abre a câmera padrão
    if (!camera.isOpened())
        qDebug("Não foi possÃ­vel abrir o a câmera padrão.");
    camera.set(CV_CAP_PROP_FRAME_WIDTH, 640.0);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480.0);

    camera >> frame; // capturo o primeiro frame

    double camfps = 30.0;   // camera.get(CV_CAP_PROP_FPS); // nao  funciona

    QString nome = parent->accessibleDescription();
    nome.append(".avi");
#ifdef Q_OS_WIN
    outputVideo = VideoWriter(nome.toStdString(), 0, camfps, frame.size(), true);  // avi sem compressao
#else
    outputVideo = VideoWriter(nome.toStdString(), CV_FOURCC('D','I','V','X'), camfps, frame.size(), true);
#endif

    if (!outputVideo.isOpened())
        qDebug("Não foi possÃ­vel abrir o arquivo de vÃ­deo.");
}

void Capture::captureFrame(Widget *parent)
{
    camera >> frame;

    // insiro informações sobre tempo/posição no vÃ­deo
    QString s = QString("Pos: X%1 Y%2").arg(parent->origin.x()).arg(parent->origin.y());
    Point p( 10, camera.get(CV_CAP_PROP_FRAME_HEIGHT) - 10 );
    putText(frame, s.toStdString() , p, FONT_HERSHEY_SIMPLEX, 0.4, Scalar::all(255.0));

    // agora converte para mostrar na tela.
    cvtColor(frame, cvtFrame, CV_BGR2RGB);
    Mat f((int)cvtFrame.rows*0.4, (int)cvtFrame.cols*0.4 ,cvtFrame.type());
    cv::resize(cvtFrame, f, f.size(), 0, 0);
    parent->cam_img = QImage((const unsigned char*)(f.data), f.cols, f.rows, QImage::Format_RGB888);
    parent->ui->label->setPixmap(QPixmap::fromImage(parent->cam_img));
}

void Capture::writeFrame()
{
    // dá saida no frame no vídeo
    outputVideo << frame;
}
