/* 
 * File:   testaFaceDetector.cpp
 * Author: andrey
 *
 * Created on 8 de Março de 2012, 11:44
 */

#include "testaFaceDetector.h"
#include "EyeDetector.h"
#include "IrisFinder.h"
#include "USTimer.h"
#include "BlobDetector.h"
#include "NoseDetector.h"
#include "NoseTipFinder.h"
#include "MouthDetector.h"
#include "MouthFinder.h"

using namespace std;

/**
 * função para testar o objeto FaceDetector
 */
bool testaFaceDetector() {
    
    WebCam cam;
    
    bool stop(false);
    FaceDetector fd;
    NoseDetector nd;
    MouthDetector md;
    EyeCascadeDetector leye(leftEye);
    EyeCascadeDetector reye(rightEye);
    IrisFinder idet;
    NoseTipFinder ntFinder;
    MouthFinder mFinder;
    BlobDetector blobDetector;

    while ( !stop ) {
        USTimer timer;
        
        cv::Mat f = cam.nextFrame();
        try {
            // localizo a face
            cv::Rect faceRectangle = fd.getFaceRegion( f );
            cv::Mat faceImage = f(faceRectangle);

            if ( faceRectangle.area() > 0) 
                cv::rectangle(f, faceRectangle, cv::Scalar(0,0,255),1,1,0);
            
//            // localizo o nariz
//            cv::Rect noseRectangle = nd.getNoseRegion( faceImage );
//            if ( noseRectangle.area() > 0 ) {
//                cv::Rect noseTmp = noseRectangle;
//                noseTmp.x += faceRectangle.x;
//                noseTmp.y += faceRectangle.y;
//                cv::rectangle( f, noseTmp, cv::Scalar(0,0,255),1,1,0 );
//                
//                // localizo a ponta do nariz
//                cv::RotatedRect noseTipEllipse = ntFinder.findNoseTip(faceImage(noseRectangle));
//                //normalizo a posição da ponta do nariz dentro do frame original
//                noseTipEllipse.center.x += faceRectangle.x + noseRectangle.x;
//                noseTipEllipse.center.y += faceRectangle.y + noseRectangle.y;
//                //ellipse(f, leftIrisEllipse, Scalar(0,0,255,0), 1, 1);
//                circle(f, noseTipEllipse.center, 4, Scalar(255, 255, 255), 1, 1, 0);
//            }
            
            // localizo a boca
            cv::Rect mouthRectangle = md.getMouthRegion( faceImage );
            if ( mouthRectangle.area() > 0 ) {
                cv::Rect mouthTmp = mouthRectangle;
                mouthTmp.x += faceRectangle.x;
                mouthTmp.y += faceRectangle.y;
                cv::rectangle( f, mouthTmp, cv::Scalar(0,0,255),1,1,0 );
                
                // localizo o centro da boca
                cv::RotatedRect mouthEllipse = mFinder.findMouth( faceImage(mouthRectangle) );
                //normalizo a posição da ponta do nariz dentro do frame original
                mouthEllipse.center.x += faceRectangle.x + mouthRectangle.x;
                mouthEllipse.center.y += faceRectangle.y + mouthRectangle.y;
                //ellipse(f, leftIrisEllipse, Scalar(0,0,255,0), 1, 1);
                circle(f, mouthEllipse.center, 4, Scalar(0, 0, 255), 1, 1, 0);
            }
            
            
            // localizo o olho esquerdo
            cv::Rect leftEyeRectangle = leye.getEyeRegion( faceImage );
            
            
            if (leftEyeRectangle.area() > 0) {
//                blobDetector.biggestBlob(faceImage(leftEyeRectangle), true );
                
                cv::RotatedRect leftIrisEllipse = idet.findIris( faceImage(leftEyeRectangle) );
                //normalizo a posição da iris dentro do frame original
                leftIrisEllipse.center.x += faceRectangle.x + leftEyeRectangle.x;
                leftIrisEllipse.center.y += faceRectangle.y + leftEyeRectangle.y;
                //ellipse(f, leftIrisEllipse, Scalar(0,0,255,0), 1, 1);
                circle(f, leftIrisEllipse.center, 4, Scalar(255, 255, 255), 1, 1, 0);
                
                // normalizo a posição do olho dentro do frame original
                leftEyeRectangle.x += faceRectangle.x;
                leftEyeRectangle.y += faceRectangle.y;
                cv::rectangle(f, leftEyeRectangle, cv::Scalar(0,255,0),1,1,0);
            }

            // localizo o olho direito
            cv::Rect rightEyeRectangle = reye.getEyeRegion( f(faceRectangle) );
            
            if (rightEyeRectangle.area() > 0) {
//                blobDetector.biggestBlob(faceImage(rightEyeRectangle), true );

                cv::RotatedRect rightIrisEllipse = idet.findIris( faceImage(rightEyeRectangle) );
                //normalizo a posição da iris dentro do frame original
                rightIrisEllipse.center.x += faceRectangle.x + rightEyeRectangle.x;
                rightIrisEllipse.center.y += faceRectangle.y + rightEyeRectangle.y;
//                ellipse(f, rightIrisEllipse, Scalar(0,0,255,0), 1, 1);
                circle(f, rightIrisEllipse.center, 4, Scalar(255, 255, 255), 1, 1, 0);

                // normalizo a posição do olho dentro do frame original
                rightEyeRectangle.x += faceRectangle.x;
                rightEyeRectangle.y += faceRectangle.y;
                cv::rectangle(f, rightEyeRectangle, cv::Scalar(255,0,0),1,1,0);
            }
            
        } catch (string e) {
            cerr << e << endl;
        }

        cv::imshow("Teste FaceDetector", f );            
        
        std::cout << "Frame processing time: " << timer.getDiffMSecondsStr() << std::endl;
        
        // pressiona uma tecla para parar
        if (cv::waitKey(5) >= 'q')
            stop = true;
    }

    return true;
}
