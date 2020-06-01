//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : LeastSquaresSolver.cpp
//  @ Date : 30/09/2012
//  @ Author : 
//
//

#include "LeastSquaresSolver.h"

using namespace cv;
using namespace std;

LeastSquaresSolver::LeastSquaresSolver() {}

LeastSquaresSolver::LeastSquaresSolver(int size, int degree) {
    polyDegree = degree;
    sampleSize = size;
}

void LeastSquaresSolver::computeSums(const Mat &xbase, const Mat &ybase, Mat &sigmaX, Mat &sigmaY) {

    sigmaX = Mat::zeros(1, polyDegree*2, CV_64F);
    sigmaY = Mat::zeros(1, polyDegree+1, CV_64F);
    Mat yteste = ybase.clone(); // não consigo passar para o mul se não clonar

    // então calculo a somatória de Y
    Scalar sumxy = cv::sum(ybase);
    sigmaY.at<double>(0,0) = (double)sumxy.val[0];

    // calcula as somatórias das potências de X
    for (int i=1; i<=polyDegree*2; i++) {
        Mat tmp;
        cv::pow(xbase, i, tmp);
        Scalar s = cv::sum(tmp);
        sigmaX.at<double>(0,i-1) = (double)s.val[0];

        Mat tmp2;
        if ((i-1) < polyDegree) {
            // calcula as somatórias das potências de x vezes y
            tmp2 = tmp.mul(yteste);
            Scalar r = cv::sum(tmp2);
            sigmaY.at<double>(0,i) = (double)r.val[0];
        }
    }

}

Mat LeastSquaresSolver::setUpLinearSystem(const Mat &xSums, const Mat &ySums) {
    // Monta a matriz A, com base nos somatórios de X
    Mat A = Mat::zeros(polyDegree+1, polyDegree+1, CV_64F);
    int k=0;
    for (int i=0; i<polyDegree+1; i++) {
        int l=0;
        for (int j=polyDegree+i; j>=i; j--) {
            if (j==0)
                A.at<double>(k,l) = (double)sampleSize;
            else
                A.at<double>(k,l) = xSums.at<double>(j-1);
            l++;
        }
        k++;
    }
cout << A << endl;

    // Monta a matriz B com base nos somatórios de X, multiplicados por Y
    Mat B = ySums.t(); // transpõe ySums
cout << B << endl;

    Mat C;
    cv::solve(A, B, C);

    return C.t();
}

/*
  A partir d um vetor de pontos de calibragem obtidos dos olhos/tela,
  aproxima a função que relaciona a posição do olho com a posição da tela.
  Retorna uma matriz (cv::Mat) com os polinômios de aproximação da função
  para X (linha 1) e Y (linha 2).
 */
Mat LeastSquaresSolver::solve(std::vector<CalibrationPair> *data) {
    // inicializa a matriz com os valores detectados do olho e os de referência da tela
    Mat xEye = Mat::zeros(data->size(), 1, CV_64F);
    Mat xScreen = Mat::zeros(data->size(), 1, CV_64F);
    Mat yEye = Mat::zeros(data->size(), 1, CV_64F);
    Mat yScreen = Mat::zeros(data->size(), 1, CV_64F);
    for (int i=0; i<data->size(); i++) {
        // eixo x
        xEye.at<double>(i, 0) = data->at(i).eye.getXRef();
        xScreen.at<double>(i, 0) = (double)data->at(i).screen.x;
        // eixo y
        yEye.at<double>(i, 0) = data->at(i).eye.getYRef();
        yScreen.at<double>(i, 0) =(double)data->at(i).screen.y;
    }

    Mat xSums, ySums;
    computeSums(xEye, xScreen, xSums, ySums);
    // monta as matrizes e resolve o sistema linear
    Mat X = setUpLinearSystem(xSums, ySums);
cout << X << endl;

    xSums = Mat();
    ySums = Mat();
    computeSums(yEye, yScreen, xSums, ySums);
    // monta as matrizes e resolve o sistema linear
    Mat Y = setUpLinearSystem(xSums, ySums);
cout << Y << endl;

    Mat result = Mat(2, X.cols, CV_64F);
    Mat r1 = result.row(0);
    Mat r2 = result.row(1);
    X.row(0).copyTo( r1 );
    Y.row(0).copyTo( r2 );

//    std::cout << "Resultado XY: " << result << std::endl;
    return result;
}