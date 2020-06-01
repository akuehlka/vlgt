#include "vlgtvideocalibrator.h"

using namespace cv;
using namespace std;

VlgtVideoCalibrator::VlgtVideoCalibrator()
{
}

VlgtVideoCalibrator::VlgtVideoCalibrator(QString path, int polydeg=4)
{
    this->filepath = path;
    this->polynomialDegree = polydeg;
}

void VlgtVideoCalibrator::calibrate(QString filename, FixedReference fixRef) {
    VlgtDataUtils du(filepath);

    QString inEyeFileName = filepath;
    QStringList fnparts = filename.split(".");
    inEyeFileName.append("/").append( fnparts.at(0) ).append(".result.txt");

    QFile inEyeFile(inEyeFileName);
    if (!inEyeFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug("Não foi possível abrir o arquivo de dados: %s", inEyeFileName.toStdString().c_str() );
        return;
    }

    // carrega a movimentação do objeto na tela
    screen = du.loadScreenData(filename);
    // encontra max para x e y da tela
    du.maxScreenCoords(screen, &maxx, &maxy);

    // carrega os dados do eye tracker, suavizando-os
    eye = du.loadEyeData(filename, fixRef, true);

//    showEyeData();

    // flags para cada ponto de interesse
    int LEFT_UPPER_DONE = 0;
    int CENTER_UPPER_DONE = 0;
    int RIGHT_UPPER_DONE = 0;
    int LEFT_MIDDLE_DONE = 0;
    int CENTER_MIDDLE_DONE = 0;
    int RIGHT_MIDDLE_DONE = 0;
    int LEFT_LOWER_DONE = 0;
    int CENTER_LOWER_DONE = 0;
    int RIGHT_LOWER_DONE = 0;
    int NSAMPLES = 5;

    // percorre os dados da tela
    for (int i=0; i < screen.size(); i++) {
        ScreenPoint region = isROI( screen.at(i) );

        if (region != SCREEN_POINT_NONE) {
            // busca coordenadas do olho para aquele frame
            map<int, EyeData>::iterator it;
            EyeData ed;

            if (region == SCREEN_POINT_LEFT_UPPER
                    && LEFT_UPPER_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                LEFT_UPPER_DONE++;
            }
            if (region == SCREEN_POINT_CENTER_UPPER
                    && CENTER_UPPER_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                CENTER_UPPER_DONE++;
            }
            if (region == SCREEN_POINT_RIGHT_UPPER
                    && RIGHT_UPPER_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                RIGHT_UPPER_DONE++;
            }
            if (region == SCREEN_POINT_LEFT_MIDDLE
                    && LEFT_MIDDLE_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                LEFT_MIDDLE_DONE++;
            }
            if (region == SCREEN_POINT_CENTER_MIDDLE
                    && CENTER_MIDDLE_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                CENTER_MIDDLE_DONE++;
            }
            if (region == SCREEN_POINT_RIGHT_MIDDLE
                    && RIGHT_MIDDLE_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                RIGHT_MIDDLE_DONE++;
            }
            if (region == SCREEN_POINT_LEFT_LOWER
                    && LEFT_LOWER_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                LEFT_LOWER_DONE++;
            }
            if (region == SCREEN_POINT_CENTER_LOWER
                    && CENTER_LOWER_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                CENTER_LOWER_DONE++;
            }
            if (region == SCREEN_POINT_RIGHT_LOWER
                    && RIGHT_LOWER_DONE < NSAMPLES) {
                it = eye.find(i);
                ed = it->second;
                RIGHT_LOWER_DONE++;
            }

            if (ed.getXRef() != 0 && ed.getYRef() != 0) {
                // cria um par de calibragem
                CalibrationPair cp(ed, screen.at(i), region);
                // adiciona-o à sequência de calibragem
                calibrationPairs.push_back(cp);
            }

        }
    }

    showCalibrationPairs();

    // processa a sequência de calibragem gerada para este vídeo
    LeastSquaresSolver lss(calibrationPairs.size(), polynomialDegree);
    Mat polynomials = lss.solve(&calibrationPairs);

    // grava o polinômio gerado para este arquivo
    QString fname = filepath;
    fname.append("/").append( fnparts.at(0) ).append(".poly");
    FileStorage fs(fname.toStdString(), FileStorage::WRITE);

    fs << "P" << polynomials;

    fs.release();

}

void VlgtVideoCalibrator::calibrateQueue(QStringList files, FixedReference fixRef) {

    for (int j=0; j<files.size(); j++) {
        qDebug("====== %s", files.at(j).toStdString().c_str());
        calibrate(files.at(j), fixRef);
    }

}

void VlgtVideoCalibrator::showCalibrationPairs() {
    qDebug("=============PARES DE CALIBRAGEM==============");
    qDebug("======Screen========================Eye=======");
    qDebug("==X==========Y================X==========Y====");
    for (int i=0; i < calibrationPairs.size(); i++) {
        CalibrationPair cp = calibrationPairs.at(i);
        qDebug("%d\t%d\t%f\t%f",cp.screen.x, cp.screen.y, cp.eye.getXRef(), cp.eye.getYRef());
    }

    qDebug("==============================================");
}

void VlgtVideoCalibrator::showEyeData() {
    qDebug("=============PARES DE DADOS===================");
    qDebug("==X======Y===================================");
    map<int,EyeData>::iterator it;
    for (it=eye.begin(); it != eye.end(); it++) {
        EyeData ed = (*it).second;

        qDebug("%f\t%f", ed.getXRef(), ed.getYRef());
    }

    qDebug("==============================================");
}

/*
 * Determina se as coordenadas passadas são um ponto de interesse para calibragem
 */
ScreenPoint VlgtVideoCalibrator::isROI(ScreenData coord) {

//    qDebug("Max x: %d", maxx );
//    qDebug("Max y: %d", maxy );

    // topo da tela
    if (coord.y <= 30) {
        if (coord.x <= 30) return SCREEN_POINT_LEFT_UPPER;
        if (coord.x > (maxx/2)-30 && coord.x < (maxx/2)+30) return SCREEN_POINT_CENTER_UPPER;
        if (coord.x > (maxx-30)) return SCREEN_POINT_RIGHT_UPPER;
    }

    // centro da tela
    if ( coord.y > (maxy/2)-30  && coord.y < (maxy/2)+30 ) {
        if (coord.x <= 30) return SCREEN_POINT_LEFT_MIDDLE;
        if (coord.x > (maxx/2)-30 && coord.x < (maxx/2)+30) return SCREEN_POINT_CENTER_MIDDLE;
        if (coord.x > (maxx-30)) return SCREEN_POINT_RIGHT_MIDDLE;
    }

    // base da tela
    if ( coord.y > (maxy-30) ) {
        if (coord.x <= 30) return SCREEN_POINT_LEFT_LOWER;
        if (coord.x > (maxx/2)-30 && coord.x < (maxx/2)+30) return SCREEN_POINT_CENTER_LOWER;
        if (coord.x > (maxx-30)) return SCREEN_POINT_RIGHT_LOWER;
    }

    return SCREEN_POINT_NONE;
}
