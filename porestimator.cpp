#include "porestimator.h"

using namespace std;
using namespace cv;

POREstimator::POREstimator()
{
}

POREstimator::POREstimator(QString polynomialFile)
{
    QFileInfo fi(polynomialFile);
    filePath = fi.path();

    QStringList fnParts = fi.fileName().split(".");
    fileName = fnParts[0];
    fileName.append(".poly");

    qDebug("Arquivo de parâmetros: %s", polynomialFile.toStdString().c_str());
    FileStorage fs;
    QString fn = filePath;
    fn.append("/").append(fileName);
    if ( fs.open(fn.toStdString(), FileStorage::READ) ) {
        fs["P"] >> polynomial;
    } else {
        qDebug("Arquivo de parâmetros não encontrado: %s", fn.toStdString().c_str() );
    }
}

vector<ScreenData> POREstimator::processFile(FixedReference fixRef, int averageSpan) {
    vector<ScreenData> result;

    RunningAverageStream rasX(averageSpan);
    RunningAverageStream rasY(averageSpan);

    if (fileName.isEmpty()) {
        qDebug("Nome do arquivo vazio.");
        return result;
    }

    if (polynomial.empty()) {
        qDebug("Polinômio não carregado.");
        return result;
    }

    VlgtDataUtils du( filePath );
    map<int,EyeData> dadosOlhos = du.loadEyeData( fileName.section('.',0,0).append(".avi"), fixRef, false );
    map<int,EyeData>::iterator it;

//    cout << "polinômios:" << endl << polynomial << endl;

    qDebug("Y\t\tY estimado");
    // para cada par de coordenadas dos olhos
    for (it=dadosOlhos.begin(); it != dadosOlhos.end(); it++) {
        double t = (double)getTickCount();

        EyeData ed = (*it).second;

        // estima x com base no polinômio
        double xval;
        int p = 0;
        for (int i=polynomial.cols-1; i>=0; i--) {
            if (p == 0)
                xval = polynomial.at<double>(0,i);
            else
                xval += pow(ed.getXRef(),p) * polynomial.at<double>(0,i);

            p++;
        }
        // trata desvios
        if (xval < 0) xval = 0;

        // estima y com base no polinômio
        double yval;
        p = 0;
        for (int i=polynomial.cols-1; i>=0; i--) {
            if (p == 0)
                yval = polynomial.at<double>(1,i);
            else
                yval += pow(ed.getYRef(),p) * polynomial.at<double>(1,i);

            p++;
        }
        // trata desvios
        if (yval < 0) yval = 0;

        xval = MIN(xval, screenSize.width);
        yval = MIN(yval, screenSize.height);
        // suavização
        xval = rasX.getValue(xval);
        yval = rasY.getValue(yval);

        Point pt(xval, yval);
        ScreenData sd( pt );

        // calcula o tempo
        double ft = ((double)getTickCount() - t) / getTickFrequency();
        sd.detectionTime = ed.processingTime;
        sd.estimationTime = ft;

        // adiciona o par de coordenadas ao resultado
        result.push_back(sd);


//        qDebug("%f\t\t%f", ed.getXRef(), xval );
//        qDebug("%f\t\t%f", ed.getYRef(), yval );

//        //imprime na tela
//        qDebug("%f\t\t%f", xval, yval);
    }

    return result;
}

void POREstimator::setScreenSize(Size s) {
    this->screenSize = s;
}
