#include <iostream>
#include "opencv.hpp"
#include "USTimer.h"

using namespace std;
using namespace cv;

int testeSolvePoly() {
    
    double auxx[5][5] = {{5231708.92290646,      173169.747364763,       5997.32501693,          222.1539,               9},
                         {162662026.362572,	5231708.92290646,	173169.747364763,	5997.32501693,          222.1539},
                         {5149160649.63808,	162662026.362572,	5231708.92290646,	173169.747364763,	5997.32501693},
                         {164887693038.991,	5149160649.63808,	162662026.362572,	5231708.92290646,	173169.747364763},
                         {5321086036962.75,	164887693038.991,	5149160649.63808,	162662026.362572,	5231708.92290646}};
    Mat x(5,5, CV_64F, auxx);
    
    double auxy[5][1] = {5782,               97750.9682,             1687656.39803202,       30193924.6363154,       572123082.410478};
    Mat y(5,1,CV_64F, auxy);

    cout << "Iniciando solução do Sistema Polinomial: " << x << endl
                                                        << y << endl;
    
    Mat z;
    
    USTimer timer;
    
    solve(x, y, z);
    
    string s(timer.getDiffMSecondsStr());
    cout << "Solução em <<"<< s <<">>ms ==================" << endl << z;

    
    return 1;
}
