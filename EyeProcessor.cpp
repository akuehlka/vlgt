/* 
 * File:   EyeProcessor.cpp
 * Author: andrey
 * 
 * Created on 15 de Julho de 2012, 15:47
 */

#include <stdlib.h>

#include "EyeProcessor.h"
#include "Face.h"
#include "cstdio"
#include "PointRunningAverageStream.h"

using namespace std;
using namespace cv;

EyeProcessor::EyeProcessor() :
        i(1),
        houghCirclesThreshold(100),
        houghLinesThreshold(100),
        lcavg(PointRunningAverageStream(10)),
        rcavg(PointRunningAverageStream(10))
{
}

EyeProcessor::EyeProcessor(const EyeProcessor& orig) {
}

EyeProcessor::~EyeProcessor() {
}

Mat EyeProcessor::borderPreservingFilter(const Mat& img, int type, Point* peak=0, const Mat& mask=Mat() ) {

    // prepara a imagem
    Mat src_gray;
    if (img.channels() == 3) 
        cvtColor(img, src_gray, CV_RGB2GRAY);
    else if (img.channels() == 1)
        img.copyTo(src_gray);
    else
        //TODO: Gerar uma exceção
        cout << "Uma imagem com 1 ou 3 canais era esperada." << endl;

    equalizeHist(src_gray, src_gray);

    Mat result;

    int ksize = 5;
    Mat kernel;

    if (type == -5) {
        // circular
        kernel = (Mat_<int>(5,5) <<   1,  1,  1,  1,  1,
                                      1,  0, -1,  0,  1,
                                      1, -1, -3, -1,  1,
                                      1,  0, -1,  0,  1,
                                      1,  1,  1,  1,  1);
    }    
    
    if (type == -4) {
        // cantos, inspirado em Zhu
        kernel = (Mat_<int>(5,5) <<   1,  1,  1,  1, -1,
                                      1,  1,  1, -1, -1,
                                      1,  1, -1, -1, -1,
                                      1, -2, -1, -1, -1,
                                      1,  1, -1, -1, -1);
    }
    if (type == -3) {
        // cantos, inspirado em Zhu
        kernel = (Mat_<int>(5,5) <<  -1,  1,  1,  1,  1,
                                     -1, -1,  1,  1,  1,
                                     -1, -1, -1,  1,  1,
                                     -1, -1, -1, -2,  1,
                                     -1, -1, -1,  1,  1);
    }
    if (type == -2) {
        // cantos, inspirado em Zhu
        kernel = (Mat_<int>(4,6) <<  -1, -1, -1,  1,  1,  1,
                                     -1, -1, -1, -1,  1,  1,
                                     -1, -1, -1, -1, -1,  1,
                                      1,  1,  1,  1,  1,  1);
    }
    if (type == -1) {
        // cantos, inspirado em Zhu
        kernel = (Mat_<int>(4,6) <<   1,  1,  1, -1, -1, -1,
                                      1,  1, -1, -1, -1, -1,
                                      1, -1, -1, -1, -1, -1,
                                      1,  1,  1,  1,  1,  1);
    }
    if (type == 1) {
        // define o filtro conforme Pedrini & Schwartz, +-p131.
        // bordas diagonais "/"
        kernel = (Mat_<int>(ksize,ksize) <<  -1, -1, -1,  1, -1,
                                             -1, -1,  2, -1,  1,
                                             -1,  2,  5,  2, -1, 
                                              1, -1,  2, -1, -1,
                                             -1,  1, -1, -1, -1);
    }
    if (type == 2) {
        // bordas horizontais (embaixo)
        kernel = (Mat_<int>(ksize,ksize) <<  -1, -1, -1, -1, -1,
                                              1,  1,  1,  1,  1,
                                             -1, -1,  4, -1, -1, 
                                              1,  1,  2,  1,  1,
                                             -1, -1, -1, -1, -1);
    }
    if (type == 3) {
        // bordas horizontais (em cima)
        kernel = (Mat_<int>(ksize,ksize) <<  -1, -1, -1, -1, -1,
                                              1,  1,  2,  1,  1,
                                             -1, -1,  4, -1, -1, 
                                              1,  1,  1,  1,  1,
                                             -1, -1, -1, -1, -1);
    }
    if (type == 4) {
        // bordas diagonais (esquerda)
        kernel = (Mat_<int>(3,3) <<   1,  1, -1,
                                      1, -2,  0,
                                     -1,  0,  0);
    }
    if (type == 5) {
        // bordas diagonais (direita)
        kernel = (Mat_<int>(3,3) <<  -1,  1,  1,
                                      0, -2,  1,
                                      0,  0, -1);
    }
    
    Rect leftRoi = Rect(0, 0, img.cols/2, img.rows);

    Point anchor = Point( -1, -1 );
    double delta = 1;
    int ddepth = -1;
    
    filter2D(src_gray, result, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
    
    // encontra a posição do pico
    double min, max;
    Point lMin;
    minMaxLoc(result, &min, &max, &lMin, peak);
    
    Mat final; 
    result.convertTo(final, CV_8UC1);
    
//    circle(final, peak, 2, Scalar(255), -1);

    return final;
}

Mat EyeProcessor::getEyeContourMask(const Mat& img) {

    Mat tmp, result;
    BlobDetector bd;

    for (int t=50; t<255; t+=10) {
        // partindo de 50, tento achar um threshold adequado para o contorno dos olhos
        threshold(img, tmp, t, 255, THRESH_BINARY_INV);
    
//        imshow("debug",tmp);

        vector<vector<Point> > blobsFound;
        // detecto somente os contornos externos
        blobsFound = bd.findBlobs(tmp);
        // somente o maior interessa
        vector<Point> theBlob;
        theBlob = bd.biggestBlob(blobsFound);

        // ajusta uma elipse
        RotatedRect rr = fitEllipse(theBlob);
        
        // se não tiver pelo menos 70% da largura
        if (rr.boundingRect().width <= (img.cols*0.7) )
            continue;

        result = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
        // desenha o hull encontrado, para ser usado como máscara de extração do olho.
        vector<vector<Point> > tmp;
        tmp.push_back(theBlob);
        drawContours(result, tmp, 0, Scalar(255), -1, 8, vector<Vec4i>(), 0);
        
        break;
    }
    
//    imshow("contours", result);
    return result;
}

Mat EyeProcessor::segmentSclera(const Mat& img) {
    Mat tmp;
    for (int t=250; t > 80; t-=10) {
        // partindo de 250, tento achar um threshold adequado
        threshold(img, tmp, t, 255, THRESH_TOZERO);
        imshow("segmentSclera", tmp);
        
        //TODO: encontrar um limite para a segmentação
    }
    return tmp;
}

/**
 * Refina a região estimada dos olhos de uma determinada face. Os resultados são 
 * atualizados diretamente no objeto Face passado como argumento.
 * @param face
 * @return 
 */
int EyeProcessor::refineEyeWindows(Face& face) {
    Mat leyeImg, reyeImg;
    Eye estimatedEye;
    
    // ========== OLHO ESQUERDO
    if (face.getLeftEye() != 0 ) {
        leyeImg = face.getEyeRegionImage(VLGT_FACE_LEFT_EYE);
        // defino um novo olho
        estimatedEye = *face.getLeftEye();
        Eye *lEye = new Eye( this->getRefinedEyeWindow(estimatedEye) );

        // TODO: re-detectar a íris depois de melhorar a imagem.
        // copio a íris que já havia sido estimada, ajustando sua posição para a nova
        // janela
        lEye->iris = estimatedEye.iris;
        lEye->iris.center.x -= lEye->x - estimatedEye.x; 
        lEye->iris.center.y -= lEye->y - estimatedEye.y;

        face.setLeftEye(lEye);
    }

    // ========== OLHO DIREITO
    if (face.getRightEye() != 0 ) {
        reyeImg = face.getEyeRegionImage(VLGT_FACE_RIGHT_EYE);
        // defino um novo olho
        estimatedEye = *face.getRightEye();
        Eye *rEye = new Eye( this->getRefinedEyeWindow(estimatedEye) );

        // TODO: re-detectar a íris depois de melhorar a imagem.
        // copio a íris que já havia sido estimada, ajustando sua posição para a nova
        // janela
        rEye->iris = estimatedEye.iris;
        rEye->iris.center.x -= rEye->x - estimatedEye.x; 
        rEye->iris.center.y -= rEye->y - estimatedEye.y;

        face.setRightEye(rEye);
    }
    
    return 0;
}

/**
 * Obtém uma janela refinada do olho, baseando-se em uma estimativa inicial do olho
 * @param eye
 * @return 
 */
Rect EyeProcessor::getRefinedEyeWindow(const Eye& eye) {
    if ( eye.eyeType != VLGT_FACE_LEFT_EYE && eye.eyeType != VLGT_FACE_RIGHT_EYE )
        throw string("O objeto esperado deve ser um olho, direito ou esquerdo.");

    int x, y, w, h;
    Rect eyeRegion;
    
    w = eye.width*0.85;
    h = eye.height*0.66;
    x = eye.iris.center.x - w/2;
    y = eye.iris.center.y - h/2; 
    
    // ajusta o offset do olho previamente estimado
    x += eye.x;
    y += eye.y;
    
    eyeRegion = Rect(x, y, w, h);
    
    // segurança para não perder a região caso a íris não esteja correta
    if (eye.iris.center.x == 0 || eye.iris.center.y == 0) {
        eyeRegion = Rect(eye.x, eye.y, eye.width, eye.height);
    }
    

    return eyeRegion;
}

void EyeProcessor::findCorners(Face& face) {
    Eye lEye = *face.getLeftEye();
    Rect lrect = this->getLeftCornerWindow(lEye);
    Mat fimg = face.getFaceImage();
    Rect rrect = this->getRightCornerWindow(lEye);
    
    Mat eyeImg = face.getEyeRegionImage(VLGT_FACE_LEFT_EYE);

    Mat slash =  (Mat_<uchar>(3,3) <<   0,  0,  1,
                                        0,  1,  0,
                                        1,  0,  0);
    Mat backslash =  (Mat_<uchar>(3,3) <<   1,  0,  0,
                                            0,  1,  0,
                                            0,  0,  1);

    Mat ml = this->borderPreservingFilter( eyeImg(lrect), -1 );

//    morphologyEx(ml, ml, MORPH_CLOSE, slash);
//    morphologyEx(ml, ml, MORPH_CLOSE, backslash);

    Mat _ml;
    resize(ml, _ml, Size(ml.cols*5, ml.rows*5));
    imshow("leftCorner",_ml);

    Mat mr = this->borderPreservingFilter( eyeImg(rrect), -2 );
    
//    morphologyEx(mr, mr, MORPH_CLOSE, slash);
//    morphologyEx(mr, mr, MORPH_CLOSE, backslash);

    Mat _mr;
    resize(mr, _mr, Size(ml.cols*5, ml.rows*5));
    imshow("rightCorner",_mr);

    // ajusta o offset
    lrect.x += lEye.x;
    lrect.y += lEye.y;
    rrect.x += lEye.x;
    rrect.y += lEye.y;
    
    rectangle(fimg, lrect, Scalar(0,255,0), 1);
    rectangle(fimg, rrect, Scalar(0,255,0), 1);
}

/**
 * A partir da estimativa da íris (e do objeto olho), define uma ROI para busca do 
 * canto esquerdo.
 * @param eye
 * @return 
 */
Rect EyeProcessor::getLeftCornerWindow(const Eye& eye) {
    int x, y, w, h;
    Rect leftRegion;
    
    w = eye.iris.boundingRect().width;
    h = eye.iris.boundingRect().height * 1.5;
    x = eye.iris.boundingRect().x - w;
    y = eye.iris.boundingRect().y; //- ((eye.iris.boundingRect().height * 0.5)/2);

    leftRegion = Rect(x, y, w, h);
    
    // verifica se não está fora da janela do olho
    if ( leftRegion.x < 0 )
        leftRegion.x = 0;
    if ( leftRegion.x > eye.x+eye.width )
        leftRegion.x = eye.width;
    if ( leftRegion.x + leftRegion.width > eye.width )
        leftRegion.width = eye.width - leftRegion.x;
    if ( leftRegion.y < 0 )
        leftRegion.y = 0;
    if ( leftRegion.y > eye.y+eye.height )
        leftRegion.y = eye.height;
    if ( leftRegion.y + leftRegion.height > eye.height )
        leftRegion.height = eye.height - leftRegion.y;
    
    return leftRegion;
}

/**
 * A partir da estimativa da íris (e do objeto olho), define uma ROI para busca do 
 * canto direito.
 * @param eye
 * @return 
 */
Rect EyeProcessor::getRightCornerWindow(const Eye& eye) {
    int x, y, w, h;
    Rect rightRegion;
    
    w = eye.iris.boundingRect().width;
    h = eye.iris.boundingRect().height * 1.5;
    x = eye.iris.boundingRect().x + (eye.iris.boundingRect().width * 0.6);
    y = eye.iris.boundingRect().y; // - ((eye.iris.boundingRect().height * 0.5)/2);

    rightRegion = Rect(x, y, w, h);

    // verifica se não está fora da janela do olho
    if ( rightRegion.x < 0 )
        rightRegion.x = 0;
    if ( rightRegion.x > eye.x+eye.width )
        rightRegion.x = eye.width;
    if ( rightRegion.x + rightRegion.width > eye.width )
        rightRegion.width = eye.width - rightRegion.x;
    if ( rightRegion.y < 0 )
        rightRegion.y = 0;
    if ( rightRegion.y > eye.y+eye.height )
        rightRegion.y = eye.height;
    if ( rightRegion.y + rightRegion.height > eye.height )
        rightRegion.height = eye.height - rightRegion.y;
    
    return rightRegion;
}

void EyeProcessor::newLocateCorners(Face& face) {
    BlobDetector bd;
    vector<vector<Point> > blobsFound;
    vector<Point> theBlob;
    
    
    // se há um olho esquerdo
    if (face.getLeftEye() != 0) {
        // imagem do olho
        Mat eyeImg = face.getEyeRegionImage(VLGT_FACE_LEFT_EYE);
        Mat irisMask = Mat::ones(eyeImg.size(), CV_8U);
        
        Eye leye = *face.getLeftEye();
//        circle(irisMask, leye.iris.center, 
//                leye.iris.boundingRect().height/2, 
//                Scalar::all(0), -1);

        Mat maskedEye;
        eyeImg.copyTo(maskedEye, irisMask);
        ImageUtils::setContrastAndBrightness(maskedEye, maskedEye, 1.4, 0);  // reduzir influência da iluminação
//        imshow("masked", maskedEye);

        int x, y, w, h;
        
//        // ===========================================
//        // parâmetros para câmera abaixo do monitor
//        w = 20;
//        x = leye.width*0.1;
//        h = 20;
//        y = leye.height*0.55;
//        Rect lHalf(x, y, w, h);
//
//        h=20;
//        x=leye.width*0.52;
//        w=30;
//        y=leye.height*0.55;
//        Rect rHalf(x, y, w, h);
//        // ===========================================

        // ===========================================
        // parâmetros para câmera acima/abaixo do monitor
        w = leye.width/3;
        x = leye.width*0.08;
        h = leye.height/2;
        y = leye.height*0.45;
        Rect lHalf(x, y, w, h);

        x=leye.width*0.52;
        y=leye.height*0.45;
        Rect rHalf(x, y, w, h);
        

rectangle(eyeImg, rHalf, Scalar(255), 1);
rectangle(eyeImg, lHalf, Scalar(255), 1);

        // elipse em volta do olho
        Point2f pt1(lHalf.x, lHalf.y);
        Point2f pt2(rHalf.x+rHalf.width, rHalf.y+rHalf.height);
        Point2f centro((pt2.x - pt1.x)/2, (pt2.y - pt1.y)/2);
        centro.x += lHalf.x;
        centro.y += rHalf.y;
        
        RotatedRect rotRec(centro, Size( pt2.x - pt1.x, pt2.y - pt1.y ), 0);
        Mat mask = Mat::zeros(eyeImg.size(), CV_8U);
        ellipse(mask, rotRec, Scalar::all(255), -1);
        Mat cornersMask;
        maskedEye.copyTo(cornersMask, mask);
//imshow("mask", cornersMask);

        // ============= CANTO ESQUERDO
        Mat lcImage = cornersMask(lHalf);
        ImageUtils::setContrastAndBrightness(lcImage, lcImage, 2, 0);  // bordas mais fortes.
        Mat lcFiltered = borderPreservingFilter(lcImage, -4); // realce de bordas
        medianBlur(lcFiltered, lcFiltered, 5);

        Scalar mean, stddev;
        meanStdDev(lcFiltered, mean, stddev);
//imshow("filter", lcFiltered);
        threshold(lcFiltered, lcFiltered, mean[0]+(stddev[0]*1), 255, CV_THRESH_BINARY);
//        openAndErode(lcFiltered, lcFiltered);
        
        // encontro blobs
        blobsFound = bd.findBlobs( lcFiltered );
        // não buscar o maior. Varrer a imagem na diagonal.
        theBlob = bd.biggestBlob(blobsFound);
        Point *p = new Point(bd.leftMost( theBlob ));
        p->x += lHalf.x;
        p->y += lHalf.y;
        *p = lcavg.getPoint( *p );
        face.getLeftEye()->leftMostCorner = p;
        
        // ============= CANTO DIREITO
        Mat rcImage = cornersMask(rHalf);
        Point pt;
        Mat rcFiltered = borderPreservingFilter(rcImage, -3, &pt);   
        medianBlur(rcFiltered, rcFiltered, 5);

        meanStdDev(rcFiltered, mean, stddev);
        threshold(rcFiltered, rcFiltered, mean[0]+(stddev[0]*1.2), 255, CV_THRESH_BINARY);
//imshow("rcFiltered", rcFiltered);
        
        
        // encontro blobs
        blobsFound = bd.findBlobs( rcFiltered );
        theBlob = bd.biggestBlob(blobsFound);
        p = new Point( bd.rightMost(theBlob) );
        p->x += rHalf.x;
        p->y += rHalf.y;
        *p = rcavg.getPoint( *p );
        face.getLeftEye()->rightMostCorner = p;
//        bd.drawBlob(eyeImg, theBlob, Point(rHalf.x, rHalf.y));


    }
}

// localiza o ponto mais abaixo e à esquerda em uma imagem binária.
Point EyeProcessor::bottomRightMost(const cv::Mat& src) {
    for(int i=src.cols; i<=0; i--) {
        for (int j=src.rows; j<=0; j--) {
            if (src.at<uchar>(i,j) >= 200) {
                return Point(i, j);
            }
        }
    }
    
    return Point();
}

// abertura e erosão específicas para esta operação
void EyeProcessor::openAndErode(const Mat& src, Mat& dst) {
    Mat elemento = getStructuringElement(MORPH_ELLIPSE, Size(2,2));
    morphologyEx(src, dst, 
            CV_MOP_OPEN,        
            elemento,             // el. estruturante
            cv::Point(-1,-1),
            1
    );
    morphologyEx(dst, dst, 
            CV_MOP_ERODE,        
            elemento,             // el. estruturante
            cv::Point(-1,-1),
            2
    );
    
}

void EyeProcessor::locateCorners(Face& face) {
    Mat eyeImg = face.getEyeRegionImage(VLGT_FACE_LEFT_EYE);
    Eye e = *face.getLeftEye();
    BlobDetector bd;
    Mat mask(eyeImg.size(), CV_8UC1, Scalar(0) );
    Mat result;
    vector<vector<Point> > blobsFound;
    vector<Point> theBlob;
    Mat ml, mr;
    Rect rl, rr;

    // =============================================================OLHO DIREITO
    if (face.getLeftEye() != 0) {
        // ======== CANTO ESQUERDO ================
        // filtro a imagem para detecção de diagonais
        ml = this->borderPreservingFilter( eyeImg, -3 );  
imshow("f1",ml);

        Mat elipse = getStructuringElement(MORPH_ELLIPSE, Size(3,3));
        morphologyEx(ml, ml, MORPH_CLOSE, elipse, Point(), 2);
        
        // um retângulo para estreitar minha ROI
        int x = e.iris.center.x - (e.width/2);
        rl = Rect(x, 
                e.iris.boundingRect().y, 
                e.width/2 , 
                e.height/2);
        // crio uma máscara tentando excluir a íris
        rectangle(mask, rl, Scalar(255), -1);
        ellipse(mask, e.iris, Scalar(0), -1, 8);
        // copio o resultado da filtragem aplicando uma máscara de minha ROI
        ml.copyTo(result, mask);
        threshold(result, result, 130, 255, THRESH_BINARY);
        // encontro blobs
        blobsFound = bd.findBlobs( result );
        theBlob = bd.biggestBlob(blobsFound);
        Point *p = new Point(bd.leftMost( theBlob ));
        face.getLeftEye()->leftMostCorner = p;
//imshow("d1",result);
//rectangle(eyeImg, e.iris.boundingRect(), Scalar(255,255,255));
        
        // ======== CANTO DIREITO  ================
        // filtro a imagem para detecção de diagonais (inversas agora)
        mr = this->borderPreservingFilter( eyeImg, -4 );

        morphologyEx(mr, mr, MORPH_CLOSE, elipse);
    
        // um retângulo para estreitar a ROI
        rr = Rect(e.iris.center.x,
                e.iris.boundingRect().y,
                e.width/3,
                e.iris.boundingRect().height*1.3);
        // crio uma máscara tentando excluir a íris
        mask = Mat(mr.size(), CV_8UC1, Scalar(0));
        rectangle(mask, rr, Scalar(255), -1);
//        circle(mask, e.iris.center, e.iris.boundingRect().width/2+10, Scalar(0), -1);
        result = Mat(mr.size(), CV_8UC1, Scalar(0));
        // copio o resultado da filtragem aplicando uma máscara de minha ROI
        mr.copyTo(result, mask);
        threshold(result, result, 130, 255, THRESH_BINARY);
        // encontro blobs
        blobsFound = bd.findBlobs( result );
        theBlob = bd.biggestBlob(blobsFound);
        Point *q = new Point(bd.rightMost( theBlob ));
        face.getLeftEye()->rightMostCorner = q;
//rectangle(mr, rr, Scalar(255));
//imshow("d2",mr);
//rectangle(eyeImg, rr, Scalar(0,255,0));
    }
    

    // =============================================================OLHO DIREITO
    if (face.getRightEye() != 0) {
        eyeImg = face.getEyeRegionImage(VLGT_FACE_RIGHT_EYE);
        e = *face.getRightEye();
        mask = Mat(eyeImg.size(), CV_8UC1, Scalar(0) );
        result = Mat();

        // ======== CANTO ESQUERDO ================
        // filtro a imagem para detecção de diagonais
        ml = this->borderPreservingFilter( eyeImg, -2 );
        // um retângulo para estreitar minha ROI
        rl = Rect(e.iris.boundingRect().x - e.iris.boundingRect().width, 
                e.iris.boundingRect().y, 
                e.iris.center.x, 
                ml.rows*0.6);
        rectangle(mask, rl, Scalar(255), -1);
        // copio o resultado da filtragem aplicando uma máscara de minha ROI
        ml.copyTo(result, mask);
        threshold(result, result, 200, 255, THRESH_BINARY);
        // encontro blobs
        blobsFound = bd.findBlobs( result );
        theBlob = bd.biggestBlob(blobsFound);
        Point *r = new Point(bd.leftMost( theBlob ));
        face.getRightEye()->leftMostCorner = r;

        // ======== CANTO DIREITO  ================
        // filtro a imagem para detecção de diagonais (inversas agora)
        mr = this->borderPreservingFilter( eyeImg, -1 );
        // um retângulo para estreitar a ROI
        rr = Rect(e.iris.center.x,
                e.iris.boundingRect().y,
                e.width - 10,
                mr.rows*0.6);
        mask = Mat(mr.size(), CV_8UC1, Scalar(0));
        rectangle(mask, rr, Scalar(255), -1);
        // copio o resultado da filtragem aplicando uma máscara de minha ROI
        mr.copyTo(result, mask);
        threshold(result, result, 200, 255, THRESH_BINARY);
        // encontro blobs
        blobsFound = bd.findBlobs( result );
        theBlob = bd.biggestBlob(blobsFound);
        Point *s = new Point(bd.rightMost( theBlob ));
        face.getRightEye()->rightMostCorner = s;
    }
    
}

void EyeProcessor::skeletonize(const Mat& _img, Mat& _dst) {
    // conforme http://felix.abecassis.me/2011/09/opencv-morphological-skeleton/
    Mat img = _img.clone();
    Mat skel(img.size(), CV_8UC1, Scalar(0));
    Mat temp(img.size(), CV_8UC1);
    Mat element = getStructuringElement(MORPH_CROSS, Size(3,3));
    
    bool done;
    do {
        morphologyEx(img, temp, MORPH_OPEN, element);
        bitwise_not(temp, temp);
        bitwise_and(img, temp, temp);
        bitwise_or(skel, temp, skel);
        erode(img, img, element);
        
        double max;
        minMaxLoc(img, 0, &max);
        done = (max == 0);
        
    } while (!done);
    
    _dst = skel;
}


// localiza a íris através de HoughCircles
void EyeProcessor::locateIris(const Mat& src, Mat& dst) 
{
    Mat src_gray;
    Mat blurred;
    vector<Vec3f> circles;

    if (src.channels() == 3) 
        src_gray = ImageUtils::toGrayScale(src, VLGT_IU_TOGRAY_SIMPLE);
    else 
        src_gray = src;

    ImageUtils::setContrastAndBrightness(src_gray, src_gray, 0.4, 0);  // bom por que uniformiza a imagem

//    GaussianBlur( src_gray, blurred, Size(9, 9), 2, 2 );
    medianBlur(src_gray, blurred, 5);  // parece ser melhor que o gaussian
    blurred = borderPreservingFilter(blurred, 3);
    blurred = borderPreservingFilter(blurred, 4);
    
imshow( "Hough Circles threshold", blurred );

// ======================================================
    Mat lines = blurred.clone();
    probabilisticHough(blurred, lines);
    imshow("lines", lines);
// ======================================================

//    if (houghCirclesThreshold <= 0)
//        houghCirclesThreshold = 100;
//    
//    // limite para o loop
//    int max_iter = 100;
//    int itercount = 0;
//    
//    do {
//        itercount++;
//        
//        if (houghCirclesThreshold <= 0)
//            break;
//    
//        /// Apply the Hough Transform to find the circles
//        int ht = houghCirclesThreshold;
////cout << "Circles thresh:" << ht << endl;
//        int lt = (ht > 0 ? ht/2 : 0);
//        HoughCircles( blurred, circles, CV_HOUGH_GRADIENT, 1, src.rows/8, ht, lt, 0, src.rows/4 );
//        
//        if (circles.size() == 0) {
//            houghCirclesThreshold -= 2;
//            continue;
//        }
//        
//        if (circles.size() > 1) {
//            houghCirclesThreshold += 2;
//            continue;
//        }
//
//    } while (circles.size() == 0 || itercount > max_iter);
//
//    /// Draw the circles detected
//    for( size_t i = 0; i < circles.size(); i++ )
//    {
//        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//        int radius = cvRound(circles[i][2]);
//        // circle center
//        circle( dst, center, 1, Scalar(0,255,0), -1, 8, 0 );
//        // circle outline
//        circle( dst, center, radius, Scalar(0,0,255), 1, 8, 0 );
//    }

    /// Show your results
//    imshow( "Hough Circles", dst );

}

//http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/sobel_derivatives/sobel_derivatives.html#sobel-derivatives
void EyeProcessor::applySobel(const Mat& src, Mat& dst)
{
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;
  
  Mat src_gray;
  if (src.channels() > 1)
        src_gray = ImageUtils::toGrayScale(src, VLGT_IU_TOGRAY_SIMPLE);
  else
      src_gray = src.clone();
      
  GaussianBlur( src_gray, src_gray, Size(3,3), 0, 0, BORDER_DEFAULT );

  /// Generate grad_x and grad_y
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  /// Gradient X
  //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );

  /// Gradient Y
  //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_y, abs_grad_y );

  /// Total Gradient (approximate)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );
  
  imshow( "Sobel", dst );
}

//http://opencv-users.1802565.n2.nabble.com/Calculate-angle-td2121415.html
float EyeProcessor::GetSlope(Point2f pt1, Point2f pt2) 
{ 
    float fSlope, fYInt, fAngle = 90, fRun = pt2.x - pt1.x; 
    bool bInfSlope = (fRun == 0); 

    if (!bInfSlope) 
    { 
        fSlope = (pt2.y - pt1.y)/fRun; 
        fAngle = (float)(180.0 * atan((double)fSlope)/CV_PI); 
        fYInt = -fSlope * pt1.x + pt1.y; 
    } 
    return fAngle; 
} 

void EyeProcessor::probabilisticHough(const Mat& src, Mat& dst)
{
    Mat canny;
    Canny(src, canny, 90, 150, 3);
    
//    imshow( "Canny", canny );
//    ImageUtils::horizProjCorners(canny);
    //http://code.opencv.org/projects/opencv/repository/revisions/master/raw/samples/cpp/tutorial_code/ImgTrans/HoughLines_Demo.cpp
    vector<Vec4i> p_lines;

    // proteção
    if (houghLinesThreshold <= 0)
        houghLinesThreshold = 100;
    
    int max_iter = 1000;
    int itercount = 0;
    
    do {
        itercount++;
    
        /// 2. Use Probabilistic Hough Transform
        HoughLinesP( canny, p_lines, 1, CV_PI/180, houghLinesThreshold, 10, 10 );
        
        if (p_lines.size() == 0) {
            houghLinesThreshold -= 2;
            continue;
        }
    
    } while (p_lines.size() == 0 || itercount > max_iter);

    /// Show the result
    for( size_t i = 0; i < p_lines.size(); i++ )
    {
        Vec4i l = p_lines[i];
        Scalar color = Scalar(255,0,0);
        Point2f pt1 = Point(l[0], l[1]);
        Point2f pt2 = Point(l[2], l[3]);
        float angulo = GetSlope(pt1, pt2);
        if ((angulo > -60 && angulo < -20) || (angulo > 5 && angulo < 60) )
            line( dst, pt1, pt2, color, 2, CV_AA);
    }

//    imshow( "HLines", dst );
}
