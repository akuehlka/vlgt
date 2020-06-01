#include "realTimeTracker.h"

using namespace std;
using namespace cv;

bool realTimeTracker() {
    string wndName = "realTimeTracker";
    
    WebCam video;
    bool stop(false);
    FaceDetector faceDetector;
    EyeProcessor eproc;
    IrisFinder irf;
    
    namedWindow(wndName, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(wndName.c_str(), 0, 0);
    
    while (!stop) {
        Mat f = video.nextFrame();
        Face face = faceDetector.getFaceRegion(f);
        face.setOriginalFrame(f);  // para uso posterior
        face.correctBrightness();
        
        if (!face.area() <= 0) {
            
            try {

                    // faço uma estimativa preliminar do olho esquerdo
                    Eye* lEye = new Eye( face.getLeftEyeEstimatedRegion(), VLGT_FACE_LEFT_EYE );
                    lEye->ifinder = &irf;
                    lEye->findIris( face.getEyeRegionImage(*lEye) );
                    face.setLeftEye( lEye );

                    eproc.newLocateCorners(face);
                
            } catch (exception e) {
                cerr << e.what() << endl;
            } catch (string s) {
                cerr << s << endl;
            }
            
        }
        
        imshow(wndName, face.getFullFrame());

        // pressiona uma tecla para parar
        if (waitKey(1) >= 'q')
            stop = true;
    }
    
    return true;
}


/***  ANOTAÇÕES
 * 
 * 
 */