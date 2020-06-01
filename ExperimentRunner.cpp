#include <iomanip>
#include <sstream>
#include <string>

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

//http://www.cplusplus.com/forum/general/15952/
string ZeroPadNumber(int num)
{
    std::ostringstream ss;
    ss << std::setw( 5 ) << std::setfill( '0' ) << num;
    return ss.str();
}

bool experimentRunner() {
    string wndName = "experimentRunner";
    string path("/home/andrey/Documentos/mestrado/vlgt_data/Experimentos1/");
    
    vector<string> filenames;
    filenames.push_back(string("vlgt_data005.avi"));
    filenames.push_back(string("vlgt_data006.avi"));
    filenames.push_back(string("vlgt_data007.avi"));
    filenames.push_back(string("vlgt_data012.avi"));
    filenames.push_back(string("vlgt_data013.avi"));
    filenames.push_back(string("vlgt_data014.avi"));
    filenames.push_back(string("vlgt_data016.avi"));
    filenames.push_back(string("vlgt_data017.avi"));
    filenames.push_back(string("vlgt_data019.avi"));
    filenames.push_back(string("vlgt_data021.avi"));
    filenames.push_back(string("vlgt_data022.avi"));
    filenames.push_back(string("vlgt_data023.avi"));
    filenames.push_back(string("vlgt_data024.avi"));
    filenames.push_back(string("vlgt_data025.avi"));
    filenames.push_back(string("vlgt_data026.avi"));
    filenames.push_back(string("vlgt_data027.avi"));
    filenames.push_back(string("vlgt_data028.avi"));
    filenames.push_back(string("vlgt_data029.avi"));
    filenames.push_back(string("vlgt_data031.avi"));
    filenames.push_back(string("vlgt_data032.avi"));
    filenames.push_back(string("vlgt_data033.avi"));
    filenames.push_back(string("vlgt_data034.avi"));
    filenames.push_back(string("vlgt_data035.avi"));
    filenames.push_back(string("vlgt_data036.avi"));
    filenames.push_back(string("vlgt_data038.avi"));

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
            face.correctBrightness();

            if (!face.area() <= 0) {

                try {

                    // faço uma estimativa preliminar do olho esquerdo
                    Eye lEye = Eye( face.getLeftEyeEstimatedRegion(), VLGT_FACE_LEFT_EYE );
                    lEye.ifinder = &ifind;
                    lEye.findIris( face.getEyeRegionImage(lEye) );
                    lEye.drawIris = false;
                    face.setLeftEye( &lEye );

//                    Eye rEye = Eye( face.getRightEyeEstimatedRegion(), VLGT_FACE_RIGHT_EYE );
//                    rEye.findIris( face.getEyeRegionImage(rEye) );
//                    face.setRightEye( &rEye );
//
//                    eproc.refineEyeWindows(face);
//                    eproc.locateCorners(face);
                    
                } catch (exception e) {
                    cerr << e.what() << endl;
                } catch (string s) {
                    cerr << s << endl;
                }

            }

            imshow(wndName, face.getFullFrame());

            /** EXPORTA OS OLHOS PARA TESTES ######################################### */
            Mat exp = face.getEyeRegionImage(VLGT_FACE_LEFT_EYE);
            char buff[100];
            string arq("./");
            arq.append("pics/").append(ZeroPadNumber(frameCount)).append(".png");
            sprintf(buff,arq.c_str());
            string nome(buff);
            imwrite(nome,exp);
            frameCount++;
            /** EXPORTA OS OLHOS PARA TESTES ######################################### */


            // pressiona uma tecla para parar
            key = waitKey(1);
            if (key >= 'q')
                stop = true;
        }
    }
    
    return true;
}
