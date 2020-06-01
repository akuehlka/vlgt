#include "vlgtdatautils.h"

using namespace std;
using namespace cv;

VlgtDataUtils::VlgtDataUtils()
{
}

VlgtDataUtils::VlgtDataUtils(QString path):
    filePath(path)
{
}

/*
 Carrega dados da tela a partir de um arquivo de dados.
 */
vector<ScreenData> VlgtDataUtils::loadScreenData(QString filename) {
    vector<ScreenData> tmp;

    QString inScreenFileName = filePath;
    QStringList fnparts = filename.split(".");
    inScreenFileName.append("/").append( fnparts.at(0) ).append(".txt");

    QFile inScreenFile(inScreenFileName);
    if (!inScreenFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug("Não foi possível abrir o arquivo de dados: %s", inScreenFileName.toStdString().c_str() );
        return tmp;
    }
    qDebug("Processando arquivo: %s", inScreenFileName.toStdString().c_str());

    int lineNumber = 0;
    while (!inScreenFile.atEnd()) {
        QByteArray line = inScreenFile.readLine();
        lineNumber++;
        // desconsidera o cabeçalho e o trailer
        if (lineNumber < 6 ||
                line.indexOf("VLGT ") >= 0 ) {
            continue;
        }

        QString l(line);
        QStringList values = l.split(QChar('\u0009'),QString::SkipEmptyParts);

        Point p( values.at(1).toInt(), values.at(2).toInt() );
        ScreenData sd(p);

        tmp.push_back(sd);

  //    qDebug("%d %d %d", values.at(0).toInt()+1, values.at(1).toInt(), values.at(2).toInt() );
    }

    inScreenFile.close();

    return tmp;

}

/*
 Busca no arquivo de dados a resolução original da tela
 */
Size VlgtDataUtils::loadOriginalScreenResolution(QString filename)
{
    Size retorno;

    QString inScreenFileName("");
    QStringList fnparts = filename.split(".");
    inScreenFileName.append("/").append( fnparts.at(0) ).append(".txt");

    QFile inScreenFile(inScreenFileName);
    if (!inScreenFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug("Não foi possível abrir o arquivo de dados: %s", inScreenFileName.toStdString().c_str() );
        return retorno;
    }

    int lineNumber = 1;
    while (!inScreenFile.atEnd()) {
        QByteArray larr = inScreenFile.readLine();

        if (lineNumber == 4) {
            QString s(larr);
            QString r = s.mid( s.indexOf( "is" )+2, s.size() ).trimmed() ;
            QStringList nrs = r.split("x");
            int x = nrs.at(0).toInt();
            int y = nrs.at(1).toInt();

            retorno = Size(x, y);
            break;
        } else if (lineNumber < 4) {
            lineNumber++;
            continue;
        }
    }

    inScreenFile.close();

    return retorno;
}

/*
 Encontra as maiores coordenadas X e Y de um conjunto de dados de tela
 */
void VlgtDataUtils::maxScreenCoords(const vector<ScreenData> &data, int *maxx, int *maxy) {
    *maxx=data.at(0).x;
    *maxy=data.at(0).y;
    for (int i=0; i<data.size(); i++ ) {
        if ( data.at(i).x > *maxx ) *maxx = data.at(i).x;
        if ( data.at(i).y > *maxy ) *maxy = data.at(i).y;
    }
}

map<int,EyeData> VlgtDataUtils::loadEyeData(QString filename, FixedReference ref, bool smoothData=false) {
    map<int,EyeData> tmp;

    RunningAverageStream rasX(10);
    RunningAverageStream rasY(10);

    QString inEyeFileName = filePath;
    QStringList fnparts = filename.split(".");
    inEyeFileName.append("/").append( fnparts.at(0) ).append(".result.txt");

    QFile inEyeFile(inEyeFileName);
    if (!inEyeFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug("Não foi possível abrir o arquivo de dados: %s", inEyeFileName.toStdString().c_str() );
        return tmp;
    }

    // pula as linhas do cabeçalho

    int linenumber=0;
    while(!inEyeFile.atEnd()) {

        QByteArray line = inEyeFile.readLine();
        QString sline(line);
        if (sline.indexOf("VLGT")>=0 ||
                linenumber < 2) {
            linenumber++;
            continue;
        }

        QStringList vars = sline.split(',',QString::SkipEmptyParts);

        // processa o frame
        // janela do olho
        int wx = vars.at(1).toInt();
        int wy = vars.at(2).toInt();
        int ww = vars.at(3).toInt();
        int wh = vars.at(4).toInt();
        Rect r(wx, wy, ww, wh);

        // Iris
        double ix = (smoothData ? rasX.getValue(vars.at(5).toDouble()) : vars.at(5).toDouble());
        double iy = (smoothData ? rasY.getValue(vars.at(6).toDouble()) : vars.at(6).toDouble());
        Point2f i(ix, iy);

        // canto esquerdo
        double lx = vars.at(7).toDouble();
        double ly = vars.at(8).toDouble();
        Point2f lc(lx, ly);

        // canto direito
        double rx = vars.at(9).toDouble();
        double ry = vars.at(10).toDouble();
        Point2f rc(rx, ry);

        // tempo de detecção
        double time = vars.at(21).toDouble();

        EyeData ed(r, lc, rc, i, ref);
        ed.processingTime = time;

//            qDebug("Frame: %d Iris -> %f %f", linenumber, ed.iris.x, ed.iris.y);

        tmp.insert( pair<int,EyeData>(linenumber-2, ed) );
        linenumber++;
    }

    inEyeFile.close();

    return tmp;

}
