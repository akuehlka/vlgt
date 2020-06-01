/* 
 * File:   ImageUtils.cpp
 * Author: andrey
 * 
 * Created on 8 de Março de 2012, 10:00
 */

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ImageUtils.h"
#include "genericutils.h"

using namespace cv;
using namespace std;

ImageUtils::ImageUtils() {
}

ImageUtils::ImageUtils(const ImageUtils& orig) {
}

ImageUtils::~ImageUtils() {
}

/**
 * Converte uma imagem RGB para gray
 * @param img   Mat contendo uma imagem RGB
 * @param type  int para identificar o tipo de conversão:
 *              VLGT_IU_TOGRAY_SIMPLE - combina os 3 canais
 *              VLGT_IU_TOGRAY_RED    - retorna o canal R
 *              VLGT_IU_TOGRAY_GREEN  - retorna o canal G
 *              VLGT_IU_TOGRAY_BLUE   - retorna o canal B
 * @return      Mat com a imagem convertida.
 */
Mat ImageUtils::toGrayScale(const Mat& img, int type) {
    if (img.channels() < 3) {
        throw string("Erro no processamento do frame. Um frame de 3 canais era esperado.");
    }

    Mat tmp;
    switch (type) {
        case VLGT_IU_TOGRAY_SIMPLE:
            cvtColor(img, tmp, CV_RGB2GRAY);
            break;
        case VLGT_IU_TOGRAY_RED:
            extractChannel(img, tmp, 0);
            break;
        case VLGT_IU_TOGRAY_GREEN:
            extractChannel(img, tmp, 1);
            break;
        case VLGT_IU_TOGRAY_BLUE:
            extractChannel(img, tmp, 2);
            break;
        default:
            // TODO: Tratar isso com exceção
            cerr << "Erro no processamento do frame. Um tipo de conversão válido era esperado.\n";
            return Mat::zeros(img.size(), CV_8UC3);
    }

    return tmp;

}

/**
 * Binariza uma imagem através da filtragem dos canais HSV
 * Valores de threshold definidos como padrão foram encontrados através de experimentação.
 * São específicos para a detecção do blob do olho inteiro
 * @param img   Mat com a imagem original
 * @param ht    int Threshold para o canal H
 * @param st    int Threshold para o canal S
 * @param vt    int Threshold para o canal V
 * @return 
 */
Mat ImageUtils::toBinaryHSV(const Mat& img, int ht, int st, int vt) {
    if (img.cols == 0 || img.rows == 0) {
        return Mat();
    }
    if (img.channels() < 3) {
        throw string("Erro no processamento do frame. Um frame de 3 canais era esperado.");
    }

    Mat hsv;
    Mat_<uchar> result = Mat::zeros(img.rows, img.cols, CV_8UC1);
    cvtColor(img, hsv, CV_BGR2HSV);

    //    // tento encontrar o melhor valor de threshold
    //    Scalar s = mean(hsv);
    //    double meanIntensity = s.val[2];
    //    double intensityThreshold = meanIntensity*0.65;

    //    double intensityThreshold = 70;  // threshold ideal para Lumix FZ-35
    double intensityThreshold = 100; // threshold ideal para webcam não encontrado

    vector<Mat> sChannels;
    split(hsv, sChannels);

    Mat teste1;
    medianBlur(sChannels[1], sChannels[1], 7);
    threshold(sChannels[1], teste1, 150, 255, THRESH_BINARY);

    //    Mat elemento = getStructuringElement(MORPH_ELLIPSE, Size(5,5));
    //    morphologyEx(teste1, teste1, 
    //            CV_MOP_CLOSE,        
    //            elemento,             // el. estruturante
    //            cv::Point(-1,-1),
    //            1
    //    );
    //    morphologyEx(teste1, teste1, 
    //            CV_MOP_OPEN,        
    //            elemento,             // el. estruturante
    //            cv::Point(-1,-1),
    //            1
    //    );

    imshow("a", teste1);


    //imshow("h", sChannels[0]);
    //imshow("s", sChannels[1]);
    //imshow("v", sChannels[2]);
    threshold(sChannels[1], result, intensityThreshold, 255, THRESH_BINARY_INV);


    //imshqow("t", result);
    return result;
}

/**
 * Pega uma imagem (grayscale), e faz a projeção horizontal dela.
 * depois, a partir desta projeção identifica os dois extremos horizontais
 * do olho contido na imagem.
 * @param img
 * @return 
 */
vector<uchar> ImageUtils::horizProjCorners(const Mat& img) {
    vector<double> res(img.cols, 0);
    vector<uchar> result;

    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++)
            res[j] += img.at<uchar > (i, j);

    Mat proj= Mat::zeros(img.size(), CV_8U);
    for (int i=0; i<res.size(); i++) {
        int h = res[i]/proj.rows;
        rectangle(proj, Point(i,h), Point(i,0), Scalar(255), -1);
    }
    
//    double sum = 0;
//    for (int i = 0; i < res.size(); i++)
//        sum += res[i];
//    double avg = sum / res.size();
//
//    // canto esquerdo
//    for (int i = 0; i < res.size(); i++)
//        if (res[i] > avg) {
//            result.push_back(i);
//            //            line(img, Point(i,0), Point(i,img.rows), Scalar(255,255,255), 1);
//            break;
//        }
//
//    // canto direito
//    for (int i = res.size(); i >= 0; i--)
//        if (res[i] > avg) {
//            result.push_back(i);
//            //            line(img, Point(i,0), Point(i,img.rows), Scalar(255,255,255), 1);
//            break;
//        }

        imshow("cornerHProj",proj);

    return result;

}

/**
 * Recebe uma imagem que contém um olho, e a binariza usando a mesma técnica 
 * usada para detectar a íris, de modo a destacar a íris e a linha da pálpebra 
 * superior, preparando a imagem para a detecção dos cantos dos olhos.
 * @param img
 * @return 
 */
Mat ImageUtils::filterCorners3(const cv::Mat& img, double threshFactor) {
    Mat tmp;
    tmp = ImageUtils::toGrayScale(img, VLGT_FINDER_TYPE_IRIS);

    tmp = ImageUtils::normalizeAndSmooth(tmp);

    // estimativa do threshold com base na média do olho
    int thresh = ImageUtils::quadraticThreshold(tmp, threshFactor);
    threshold(tmp, tmp, thresh, 255, CV_THRESH_BINARY_INV);

    Mat elemento = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(tmp, tmp,
            CV_MOP_OPEN,
            elemento, // el. estruturante
            cv::Point(-1, -1),
            1
            );
    //imshow("filterCorners3", tmp);

    return tmp;
}

/**
 * Recebe uma imagem que contém um olho, e faz uma filtragem (pyrMeanShift)
 * depois faz um sobel horizontal nela, preparando a imagem para detectar os
 * cantos do olho.
 * @param img
 * @return 
 */
Mat ImageUtils::filterCorners2(const cv::Mat& img) {

    Rect leftHalf(0, 0, img.cols / 2.2, img.rows);
    Rect rightHalf(img.cols / 2, 0, img.cols / 2, img.rows);

    // limpa ruídos
    Mat tmp;
    pyrMeanShiftFiltering(img, tmp, 2, 40, 1);
    //    imshow("debug", tmp);

    // prepara a imagem
    Mat src_gray;
    cvtColor(tmp, src_gray, CV_RGB2GRAY);
    equalizeHist(src_gray, src_gray);
    //    threshold(src_gray, src_gray, 150, 255, CV_THRESH_TRUNC);
    //    imshow("debug", src_gray);

    // sobel horizontal
    Mat grad_y, abs_grad_y;
    int ddepth = CV_16S;
    int delta = 0;
    int scale = 1;

    /// Gradient Y
    Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    threshold(abs_grad_y, abs_grad_y, 130, 255, CV_THRESH_TOZERO);

    //    imshow("debug", abs_grad_y);
    horizProjCorners(abs_grad_y);

    return Mat();
}

/**
 * Recebe uma imagem de um olho, e faz uma filtragem por convolução, buscando
 * realçar o olho, para detecção dos cantos.
 * @param img
 * @return 
 */
Mat ImageUtils::filterCorners(const Mat& img) {

    // prepara a imagem
    Mat src_gray;
    cvtColor(img, src_gray, CV_RGB2GRAY);
    equalizeHist(src_gray, src_gray);

    // define o filtro conforme ("Subpixel Eye Gaze Tracking" by Jie Zhu, Jie Yang)
    //    Size s = Size(4,6);
    //    Mat kernelLeft = Mat::ones(s, CV_32FC1);
    //    kernelLeft.at<Vec2f>(0,0) = -1;
    //    kernelLeft.at<Vec2f>(0,1) = -1;
    //    kernelLeft.at<Vec2f>(0,2) = -1;
    //    kernelLeft.at<Vec2f>(1,0) = -1;
    //    kernelLeft.at<Vec2f>(1,1) = -1;
    //    kernelLeft.at<Vec2f>(1,2) = -1;
    //    kernelLeft.at<Vec2f>(1,3) = -1;
    //    kernelLeft.at<Vec2f>(2,0) = -1;
    //    kernelLeft.at<Vec2f>(2,1) = -1;
    //    kernelLeft.at<Vec2f>(2,2) = -1;
    //    kernelLeft.at<Vec2f>(2,3) = -1;
    //    kernelLeft.at<Vec2f>(2,4) = -1;
    Size s = Size(4, 4);
    Mat kernelLeft = Mat::ones(s, CV_32FC1);
    kernelLeft.at<Vec2f > (0, 3) = -1;
    kernelLeft.at<Vec2f > (1, 2) = -1;
    kernelLeft.at<Vec2f > (1, 3) = -1;
    kernelLeft.at<Vec2f > (2, 1) = -1;
    kernelLeft.at<Vec2f > (2, 2) = -1;
    kernelLeft.at<Vec2f > (2, 3) = -1;
    kernelLeft.at<Vec2f > (3, 0) = -1;
    kernelLeft.at<Vec2f > (3, 1) = -1;
    kernelLeft.at<Vec2f > (3, 2) = -1;
    kernelLeft.at<Vec2f > (3, 3) = -1;
    Rect leftRoi = Rect(0, 0, img.cols / 2, img.rows);

    Point anchor = Point(-1, -1);
    double delta = 0;
    int ddepth = -1;

    Mat result;
    filter2D(src_gray, result, ddepth, kernelLeft, anchor, delta, BORDER_DEFAULT);

    Mat tmp;
    result.convertTo(tmp, CV_8UC1);

    Mat bw; // = Mat::zeros(leftRoi.height, leftRoi.width, CV_8UC1);
    threshold(result, bw, 180, 255, CV_THRESH_TRUNC);
    threshold(bw, bw, 80, 255, CV_THRESH_BINARY_INV);

    //    Mat elemento = getStructuringElement(MORPH_ELLIPSE, Size(3,5));
    //    morphologyEx(bw, bw, 
    //            CV_MOP_CLOSE,        
    //            elemento,             // el. estruturante
    //            cv::Point(-1,-1),
    //            2
    //    );
    //    morphologyEx(bw, bw, 
    //            CV_MOP_OPEN,        
    //            elemento,             // el. estruturante
    //            cv::Point(-1,-1),
    //            2
    //    );
    //    morphologyEx(bw, bw, 
    //            CV_MOP_ERODE,        
    //            elemento,             // el. estruturante
    //            cv::Point(-1,-1),
    //            2
    //    );

    //    if (!result.empty() ) 
    //        imshow("filtro", bw);

    return bw;
}

/**
 * Experiência para tentar localizar o canto dos olhos através do goodFeaturesToTrack
 * @param img
 */
void ImageUtils::findCorners(Mat img) {

    Mat src_gray;
    cvtColor(img, src_gray, CV_RGB2GRAY);
    equalizeHist(src_gray, src_gray);
    //    medianBlur(src_gray, src_gray, 9);
    Mat elemento = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(src_gray, src_gray,
            CV_MOP_CLOSE,
            elemento, // el. estruturante
            cv::Point(-1, -1),
            1
            );


    /// Parameters for Shi-Tomasi algorithm
    vector<Point2f> corners;
    double qualityLevel = 0.05;
    double minDistance = 10;
    int blockSize = 5;
    bool useHarrisDetector = false;
    double k = 0.04;
    int maxCorners = 1;

    goodFeaturesToTrack(src_gray,
            corners,
            maxCorners,
            qualityLevel,
            minDistance,
            Mat(),
            blockSize,
            useHarrisDetector,
            k);

    /// Draw corners detected
    cout << "** Number of corners detected: " << corners.size() << endl;
    int r = 2;
    for (int i = 0; i < corners.size(); i++) {
        circle(img, corners[i], r, Scalar(255, 0, 0), -1, 8, 0);
    }

    /// Show what you got
    imshow("debug", src_gray);
}

Mat ImageUtils::toBinaryEyeCorners(const Mat& img) {
    if (img.empty())
        return Mat();

    if (img.channels() < 3) {
        throw string("Erro no processamento do frame. Um frame de 3 canais era esperado.");
    }

    Mat gray;

    Mat_<uchar> result = Mat::zeros(img.rows, img.cols, CV_8UC1);
    gray = ImageUtils::toGrayScale(img, VLGT_IU_TOGRAY_SIMPLE);

    // tento encontrar o melhor valor de threshold
    double intensityThreshold = ImageUtils::cubicThreshold(gray);

    equalizeHist(gray, gray);
    blur(gray, gray, Size(3, 3));

    //    cout << intensityThreshold << endl;
    threshold(gray, result, intensityThreshold, 255, THRESH_BINARY_INV);

    Mat elemento = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(result, result,
            CV_MOP_ERODE,
            elemento, // el. estruturante
            cv::Point(-1, -1),
            1
            );

    imshow("open", result);

    return result;
}

int ImageUtils::hProjection(const Mat& src) {
    // src deve ser uma imagem em grayscale
    // a função retorna o ponto no eixo x com maior intensidade

    //    namedWindow( "X Projection",CV_WINDOW_AUTOSIZE );
    int maxx = 0;
    int maxval = 0;
    // imagem para criar o gráfico de projeção
    //    Mat res = Mat::zeros(100, src.cols, CV_8U);

    for (int i = 0; i < src.cols; i++) {
        int col_sum = 0;
        for (int j = 0; j < src.rows; j++) {
            col_sum += src.at<uchar > (j, i);
        }
        if (col_sum > maxval) {
            maxval = col_sum;
            maxx = i;
        }
        // plota uma linha no gráfico de projeção
        //        rectangle( res, Point(i,0), Point(i,col_sum/100), CV_RGB(255,255,255), CV_FILLED );
    }

    //    imshow("X Projection", res);

    return maxx;
}

int ImageUtils::vProjection(const Mat& src) {
    // src deve ser uma imagem em grayscale
    // a função retorna o ponto no eixo y com maior intensidade

    //    namedWindow( "Y Projection",CV_WINDOW_AUTOSIZE );
    int maxy = 0;
    int maxval = 0;
    // imagem para criar o gráfico de projeção
    //    Mat res = Mat::zeros(src.rows, 100, CV_8U);

    for (int i = 0; i < src.rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < src.cols; j++) {
            row_sum += src.at<uchar > (i, j);
        }
        if (row_sum > maxval) {
            maxval = row_sum;
            maxy = i;
        }
        // plota uma linha no gráfico de projeção
        //        rectangle( res, Point(0,i), Point(row_sum/100,i), CV_RGB(255,255,255), CV_FILLED );
    }

    //    imshow ("Y Projection", res);

    return maxy;
}

/**
 * Retorna o ponto onde está localizado o canto do olho, baseado na projeção
 * @param img           Mat com a imagem
 * @return              Point com o ponto encontrado.
 */
Point ImageUtils::eyeCornerProjection(const cv::Mat& img) {
    int x = ImageUtils::hProjection(img);
    int y = ImageUtils::vProjection(img);
    return Point(x, y);
}

/**
 * Normaliza uma imagem, colorida ou grayscale. Usada para corrigir problemas de 
 * iluminação para rosto e olhos.
 */
void ImageUtils::normalizeAny(const cv::Mat& img, Mat dst) {
    vector<Mat> chans;

    if (img.channels() == 1) {
        dst = Mat(img.size(), CV_8UC1);
        normalize(img, dst, 0, 255, CV_MINMAX);
    } else if (img.channels() == 3) {
        split(img, chans);
        normalize(chans[0], chans[0], 0, 255, CV_MINMAX);
        normalize(chans[1], chans[1], 0, 255, CV_MINMAX);
        normalize(chans[2], chans[2], 0, 255, CV_MINMAX);
        merge(chans, dst);
    }
    //imshow("olho", dst);
    //    return dst;
}

/**
 * Normaliza e suaviza uma imagem. Usada para corrigir problemas de iluminação 
 * para rosto e olhos, e reduzir ruído
 */
Mat ImageUtils::normalizeAndSmooth(const cv::Mat& img) {
    Mat dst;
    vector<Mat> chans;

    if (img.channels() == 1) {
        normalize(img, dst, 0, 255, CV_MINMAX);
    } else if (img.channels() == 3) {
        split(img, chans);
        normalize(chans[0], chans[0], 0, 255, CV_MINMAX);
        normalize(chans[1], chans[1], 0, 255, CV_MINMAX);
        normalize(chans[2], chans[2], 0, 255, CV_MINMAX);
        merge(chans, dst);
    }
    dst = ImageUtils::smooth(dst);
    //imshow("olho", dst);
    return dst;
}

/**
 * Suaviza uma imagem. 
 */
Mat ImageUtils::smooth(const cv::Mat& img) {
    Mat dst;

    blur(img, dst, Size(5, 5), Point(2, 2), 0);

    return dst;
}

/**
 * Calcula um Threshold para limiarização, baseado na média da imagem, aplicando 
 * uma função quadrática. Funciona bem para segmentação da íris.
 * @param img
 * @return 
 */
double ImageUtils::quadraticThreshold(const Mat& img, double thFactor) {
    Scalar s = mean(img);
    double meanIntensity = *s.val * 1.4;
    return (double) (pow(meanIntensity, 2) / 255) * thFactor;
}

/**
 * Calcula um Threshold para limiarização, baseado na média da imagem, aplicando 
 * uma função cúbicca. Funciona bem para determinar os cantos dos olhos.
 * @param img
 * @return 
 */
double ImageUtils::cubicThreshold(const cv::Mat& img) {
    Scalar s = mean(img);
    double meanIntensity = *s.val;
    meanIntensity -= 128;
    double intensityThreshold = ((pow(meanIntensity, 3)) / 25500) + 80;
    return intensityThreshold;
}

/**
 * Ajusta o canal V da imagem, para reduzir o efeito de sombras
 * @param img
 * @param dst
 */
void ImageUtils::adjustVChannel(const Mat& img, Mat dst) {
    //    imshow("Original",img);

    // converte para HSV
    Mat hsv;
    cvtColor(img, hsv, CV_RGB2HSV);

    // separa os canais
    vector<Mat> chans;
    split(hsv, chans);

    // encontra mínimo e máximo do canal 2 (V)
    double min, max;
    minMaxLoc(chans[2], &min, &max);
    //    cout << "Min " << min << ", Max " << max << endl;

    imAdjust(chans[2], chans[2], 0.1, 0.5, 0.5, 1.0);

    // funde os canais novamente
    merge(chans, hsv);
    cvtColor(hsv, dst, CV_HSV2RGB);
    //    imshow("Result",dst);
}

void ImageUtils::imAdjust(Mat img, Mat dst, double loIn, double hiIn, double loOut, double hiOut) {
    if (img.channels() > 1) {
        cout << "A imagem so pode ter 1 canal." << endl;
        return;
    }

    double amplitude = hiIn * 255 - loIn * 255;
    double factor = amplitude / (hiOut * 255 - loOut * 255);


    Mat tmp = Mat::zeros(img.size(), CV_8UC1);
    for (int i = 0; i < img.rows; i++) {
        uchar* orig = img.ptr<uchar > (i);
        uchar* dest = tmp.ptr<uchar > (i);
        for (int j = 0; j < img.cols; j++) {
            if (orig[j] >= loIn * 255 &&
                    orig[j] <= hiIn * 255) {
                // faz a conversão
                dest[j] = saturate_cast<uchar > (orig[j] / factor);
            } else
                // mantém como está
                dest[j] = orig[j];
        }
    }
    //    imshow("imadjust",tmp);

    tmp.copyTo(dst);
}

void ImageUtils::setContrastAndBrightness(const cv::Mat& img, cv::Mat dst, double alpha, int beta) {

    // http://docs.opencv.org/doc/tutorials/core/basic_linear_transform/basic_linear_transform.html
    img.convertTo(dst, -1, alpha, beta);
    
//    imshow("Bright", dst);
}

void ImageUtils::showHistogram(const Mat& img) {
    // http://www.aishack.in/2010/07/drawing-histograms-in-opencv/
    int numBins = 256;
    int histSize[] = {numBins};
    float hranges[] = {0.0, 255.0};
    const float* ranges[] = { hranges };
    int channels[] = {1};;
    
    MatND hist;
    calcHist( &img, 
            2, 
            channels, 
            Mat(),
            hist,
            1,
            histSize , 
            ranges);
    
    double minVal=0;
    double maxVal=0;
    minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    
    Mat histImg(numBins, numBins, CV_8U, Scalar(0));
    int hpt = static_cast<int>(0.9*numBins);
    
    for( int h=0; h < numBins; h++) {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal*hpt/maxVal);
        
        line(histImg, Point(h,numBins), Point(h,numBins-intensity),
                Scalar::all(255));
    }
    
    imshow("Histogram", histImg);
}

void ImageUtils::gammaCorrection(const Mat& img, Mat dst, double gamma) {
    double gammaCorr = 1 / gamma;
    
    pow(img, gammaCorr, dst);
    convertScaleAbs(dst, dst, 1, 0);
    
    imshow("gammaCorrection", dst);
}

void ImageUtils::differenceOfGaussian(const cv::Mat& src, cv::Mat dst) {
    Mat gauss1, gauss2;
    GaussianBlur( src, gauss1, Size(3,3), 0);
    GaussianBlur( src, gauss2, Size(5,5), 0);
    subtract(gauss2, gauss1, dst);
    
    imshow("DOG",dst);
}