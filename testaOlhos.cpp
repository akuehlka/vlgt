


#include "Face.h"
#include "WebCam.h"
#include "FaceDetector.h"
#include "EyeDetector.h"
#include "MouthDetector.h"
#include "IrisFinder.h"
#include "EyeBlobDetector.h"
#include "VideoFile.h"
#include "EyeProcessor.h"
#include "ExperimentRunner.h"

using namespace std;
using namespace cv;

bool testaOlhos() {
    string wndName = "testaOlhos";
    string path("./pics/");
    char key;
    IrisFinder ifind;
    EyeProcessor eproc;

    for (int f=1; f<9558 ; f++) {
        cout << "==> FrameNR: " << f << endl;
        
        try {
        
            string filename(path);
            filename.append(ZeroPadNumber(f)).append(".png");

            // abre arquivo
            Mat im = imread(filename);

            Face face;
            face.setRightEye(0);
            face.setOriginalFrame(im);
            Eye* lEye = new Eye( Rect(0,0,im.cols, im.rows), VLGT_FACE_LEFT_EYE );
            lEye->ifinder = &ifind;
            lEye->findIris( im );
            lEye->refineROI();
            face.setLeftEye(lEye);
            
            
//            int h = lEye->iris.boundingRect().height * 1.3;
//            int w = MIN( lEye->iris.boundingRect().width * 3, im.cols*0.75 );
//            int x = lEye->iris.center.x - (w/2);
//            int y = lEye->iris.center.y - (h/2)*0.8;
//            Rect r(x, y, w, h);
//            rectangle(im, r, Scalar(255), 1, 0);
            
//            Mat olho = im(lEye);
//            eproc.locateIris(olho, im);


            imshow(wndName, face.getFullFrame());
        }  catch (exception e) {
            cerr << e.what() << endl;
        } catch (string s) {
            cerr << s << endl;
        }
        
        key = waitKey(0);
        
        if (key == 'n')
            f += 500;
        if (key == 'q')
            break;
    }
    
    return true;
}


/***  ANOTAÇÕES
 * 
 * 
 */

