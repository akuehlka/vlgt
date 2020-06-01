


#include "Face.h"
#include "WebCam.h"
#include "FaceDetector.h"
#include "EyeDetector.h"
#include "MouthDetector.h"
#include "IrisFinder.h"
#include "EyeBlobDetector.h"
#include "VideoFile.h"
#include "EyeProcessor.h"

using namespace std;
using namespace cv;

bool testaModeloFace(int exp) {
    string wndName = "testaModeloFace";
    
    string path;
    vector<string> filenames;
    if (exp == 1) {
        path = string("/home/andrey/Documentos/mestrado/vlgt_data/Experimentos1/");
        filenames.push_back(string("vlgt_data005.avi"));
        filenames.push_back(string("vlgt_data007.avi"));
        filenames.push_back(string("vlgt_data012.avi"));
        filenames.push_back(string("vlgt_data014.avi"));
    }
    if (exp == 2) {
        path = string("/home/andrey/Documentos/mestrado/vlgt_data/Experimentos2/");
        filenames.push_back(string("vlgt_data001.avi"));
        filenames.push_back(string("vlgt_data002.avi"));
        filenames.push_back(string("vlgt_data003.avi"));
        filenames.push_back(string("vlgt_data004.avi"));
        filenames.push_back(string("vlgt_data005.avi"));
        filenames.push_back(string("vlgt_data007.avi"));
        filenames.push_back(string("vlgt_data012.avi"));
        filenames.push_back(string("vlgt_data014.avi"));
        filenames.push_back(string("vlgt_data015.avi"));
        filenames.push_back(string("vlgt_data016.avi"));
        filenames.push_back(string("vlgt_data017.avi"));
        filenames.push_back(string("vlgt_data018.avi"));
    }
    if (exp == 3) {
        path = string("/home/andrey/Documentos/mestrado/vlgt_data/Experimentos3/");
//        filenames.push_back(string("vlgt_data001.avi"));
//        filenames.push_back(string("vlgt_data002.avi"));
//        filenames.push_back(string("vlgt_data003.avi"));
//        filenames.push_back(string("vlgt_data004.avi"));
//        filenames.push_back(string("vlgt_data005.avi"));
//        filenames.push_back(string("vlgt_data006.avi"));
//        filenames.push_back(string("vlgt_data007.avi"));
//        filenames.push_back(string("vlgt_data008.avi"));
//        filenames.push_back(string("vlgt_data009.avi"));
//        filenames.push_back(string("vlgt_data010.avi"));
        filenames.push_back(string("vlgt_data011.avi"));
        filenames.push_back(string("vlgt_data012.avi"));
        filenames.push_back(string("vlgt_data013.avi"));
        filenames.push_back(string("vlgt_data014.avi"));
        filenames.push_back(string("vlgt_data015.avi"));
    }
    
    int frameCount = 1;
    char key;
    IrisFinder ifind;
    
    for (int f=0; f<filenames.size() || key=='q'; f++) {
        
        string filename(path);
        VideoFile video(filename.append(filenames[f]));
        bool stop(false);
        FaceDetector faceDetector;
        EyeProcessor eproc;
    
        namedWindow(wndName, CV_WINDOW_AUTOSIZE);
        cvMoveWindow(wndName.c_str(), 0, 0);

        while (!stop) {
            Mat f = video.nextFrame();
            if (f.empty()) break;
            Face face = faceDetector.getFaceRegion(f);
            face.setOriginalFrame(f);  // para uso posterior
//            face.correctBrightness();

            if (!face.area() <= 0) {

                try {

                    // faço uma estimativa preliminar do olho esquerdo
                    Eye* lEye = new Eye( face.getLeftEyeEstimatedRegion(), VLGT_FACE_LEFT_EYE );
                    lEye->ifinder = &ifind;
                    lEye->findIris( face.getEyeRegionImage(*lEye) );
                    face.setLeftEye( lEye );
//                    lEye->refineROI();

                    eproc.newLocateCorners(face);

                } catch (exception e) {
                    cerr << e.what() << endl;
                } catch (string s) {
                    cerr << s << endl;
                }

            }

            imshow(wndName, face.getFullFrame());
//            imshow(wndName, f);
            
            // pressiona uma tecla para parar
            if (waitKey(1) == 'q')
                     stop = true;
        }
    }
    
    return true;
}


/***  ANOTAÇÕES
 * 
 * 
 */