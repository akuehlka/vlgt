#include "CalibrationPair.h"

using namespace cv;
using namespace std;

CalibrationPair::CalibrationPair() {}

CalibrationPair::CalibrationPair(EyeData e, ScreenData s, ScreenPoint p) :
    eye(e),
    screen(s),
    screenPoint(p)
{}
