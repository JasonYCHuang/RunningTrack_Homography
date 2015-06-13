#ifndef SYSTEM
#define SYSTEM

#include <opencv2/core/core.hpp>
#include "lib_misc.h"
#include "lib_math.h"
using namespace cv;
using namespace std;

class System {

public:
    // Camera parameters
    struct calibration {
        double fu;          // focal length in u-direction.
        double fv;          // focal length in v-direction.
        Point2f center;     // camera center position on the image.
        Mat K;              // camera internal matrix.

        void resetCameraInternalMatrix() {
            K = (Mat_<double>(3,3) << fu, 0.00*fu, center.x,
                                      0,  fv,      center.y,
                                      0,  0,            1);     // camera internal matrix.
        }
    };

    // Settings for processing the bird view.
    struct setting  {
        int num_lines_for_vline;
        int num_lines_for_vpoint;
    };

};
#endif // SYSTEM

