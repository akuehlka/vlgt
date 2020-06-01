/* 
 * File:   IrisFinder.cpp
 * Author: andrey
 * 
 * Created on 12 de Março de 2012, 16:14
 */

#include "FeatureFinder.h"
#include "IrisFinder.h"

using namespace cv;
using namespace std;

IrisFinder::IrisFinder(): 
    FeatureFinder( VLGT_FINDER_TYPE_IRIS ),
    irisBrightnessAlpha(1.5),
    irisBrightnessBeta(80)
{
}

IrisFinder::IrisFinder(const IrisFinder& orig) {
}

IrisFinder::~IrisFinder() {
}

void IrisFinder::enhanceImage(const Mat& src) {

    this->img = ImageUtils::toGrayScale(src, this->grayScaleCvtType);
    Mat el = getStructuringElement(MORPH_ELLIPSE, Size(3,3));
    morphologyEx(this->img, this->img,
            CV_MOP_CLOSE,
            el,             // el. estruturante
            cv::Point(-1,-1),
            2
    );
    medianBlur(this->img, this->img, 3);
//imshow("1", this->img);

    this->img = ImageUtils::normalizeAndSmooth(this->img);
    ImageUtils::setContrastAndBrightness(this->img, this->img, this->irisBrightnessAlpha, this->irisBrightnessBeta);
//imshow("2", this->img);

    // estimativa do threshold com base na média do olho
    Scalar mean, stddev;
    meanStdDev(this->img, mean, stddev);
    ffThreshold = mean[0]-(stddev[0]*2);

    threshold(this->img, this->img, ffThreshold, 255, CV_THRESH_BINARY_INV);
//imshow("3", this->img);

    Mat elemento = getStructuringElement(MORPH_ELLIPSE, Size(5,5));
    morphologyEx(this->img, this->img,
            CV_MOP_ERODE,
            elemento,             // el. estruturante
            cv::Point(-1,-1),
            1
    );
    morphologyEx(this->img, this->img,
            CV_MOP_DILATE,
            elemento,             // el. estruturante
            cv::Point(-1,-1),
            1
    );
//    imshow("iris",this->img);

}

float IrisFinder::circularityCoeff(const RotatedRect &elipse)
{
    int w = elipse.boundingRect().width;
    int h = elipse.boundingRect().height;

    float coeff = MAX(w,h)/MIN(w,h);

//cout << "Coeficiente de circularidade: " << coeff << endl;

    return coeff;
}


bool IrisFinder::isNearlyRound(const cv::RotatedRect& iris) {
    
    float coeff = circularityCoeff(iris);

    if (coeff > 0.8 && coeff < 1.4)
        return true;
    
    return false;
}

RotatedRect IrisFinder::findIris(const cv::Mat& src) {
    if (src.empty())
        return RotatedRect();
    
    if (src.channels() < 3)
        throw std::string("Uma imagem com 3 canais era esperada.");

    this->enhanceImage(src);
    
    vector<RotatedRect> result = this->findEllipses();
    
    if (result.size() == 0)
        return RotatedRect();
    
    // o diâmetro da íris deve ser aproximadamente 10,1% da largura da face.
    
    int irisArea = (result[0]).boundingRect().area(); 
    int eyeArea = src.cols*src.rows;
    
    // TODO: escolher a melhor elipse para retornar
    return findAppropriateEllipse(result);
}

vector<RotatedRect> IrisFinder::findEllipses() {
    // TODO: não  permitir uma imagem não-binarizada

//imshow("debug", this->img);
//Mat dbg = Mat::zeros(this->img.rows, this->img.cols, CV_8UC3);
    
    vector<vector<Point> > contours;
    findContours( this->img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );
    
    vector<RotatedRect> retorno;

    // um retângulo para delinear o "centro" da janela de busca
    int w = this->img.cols * 0.6;
    int x = (this->img.cols - w)/2;
    int h = this->img.rows * 0.6;
    int y = (this->img.rows - h)/2;
    Rect centro(x, y, w, h);

    // ajusta as elipses
    for( int i = 0; i < contours.size(); i++ ) { 
        // descarto contornos que não podem ser elipses.
        size_t count = contours[i].size();
        if( count < 6 )
            continue;
        
        Mat pointsf;
        Mat(contours[i]).convertTo(pointsf, CV_32F);
        RotatedRect box = fitEllipse(pointsf);


        // se não estiver aproximadamente no centro da janela de busca, descarta
        if (!centro.contains(box.center))
            continue;

//        // somente se for aproximadamente redonda
//        if (!isNearlyRound(box))
//            // se a "redondeza" ultrapassar um limite, descarta
//            continue;

//        // verifica o tamanho
//        if ( MAX(box.size.width, box.size.height) < this->img.cols/10 ) {
////            //se for muito pequena, verifica a proporção
////            float ratio = MAX(box.size.width, box.size.height)/MIN( box.size.width, box.size.height);
////            if (ratio > 1.4) {
//                continue;
////            }

//        }

        retorno.push_back(box);

    }
    
// com o uso da média/desvio para seleção do limiar, o fator tornou-se irrelevante.
//    for (int i=0; i < retorno.size(); i++) {
//        RotatedRect r = RotatedRect(retorno[i]);

//        if (MAX( r.size.width, r.size.height ) > this->img.cols/4 ) {
//            // se o tamanho de algum objeto ultrapassar um limite,
//            // decremento o fator de threshold
//            thresholdFactor *= 0.9;
//            break;
//        }
//        if (MIN( r.size.width, r.size.height ) < this->img.cols/8 ) {
//            // se o tamanho de algum objeto ultrapassar um limite mínimo,
//            // incremento o fator de threshold
//            thresholdFactor *= 1.1;
//            break;
//        }

//    }
    
//    // se nenhuma elipse foi encontrada, incrementa o fator threshold
//    if (retorno.size() == 0) {
//        thresholdFactor += 0.1;
//    }
    
//    cout << "thFact " << thresholdFactor << endl;
    return retorno;
}

// escolhe a melhor elipse para eleger a íris.
RotatedRect IrisFinder::findAppropriateEllipse(const vector<RotatedRect> &ellipses)
{
    vector<double> scores(ellipses.size());
    Point centro( this->img.cols/2, this->img.rows/2 );

    for (int i=0; i<ellipses.size(); i++)
    {
        RotatedRect r = ellipses[i];

        // primeiro critério: coeficiente de circularidade
        double cc = circularityCoeff(r);

        // segundo critério: distância do centro da janela de busca
        double dist = 1/sqrt(pow(centro.x - r.center.x, 2) + pow(centro.y - r.center.y, 2));

        // TODO: terceiro critério: tamanho
        double tam = r.boundingRect().area();

        scores[i] = (cc * 0.15) + (tam * 0.25) + (dist * 0.5);
    }

    int maior = 0;
    for (int i=0; i<scores.size(); i++)
        if (scores[i] > scores[maior])
            maior = i;

    return ellipses[maior];
}
