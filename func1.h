#ifndef FUNC_H
#define FUNC_H
    #include <iostream>
    #include <sstream>
    #include <stdio.h>

    #include <opencv2/core/core.hpp>
    #include <opencv2/imgproc/imgproc.hpp>
    #include <opencv2/calib3d/calib3d.hpp>
    #include <opencv2/highgui/highgui.hpp>

    using namespace cv;
    using namespace std;

    const Point2f  CAM_CENTER(442.21533, 284.83506);
    const Point2f  IMG_CENTER(442.21533, 284.83506);  //(400, 300);

    const Point2f  V_TOP(442.21533, 0);
    const Point2f  V_BOT(442.21533, 600);
    const Point2f  H_LFT(0, 284.83506);
    const Point2f  H_RIT(800, 284.83506);

    const double  FOCUS_1 = 801.08310;
    const double  FOCUS_2 = 805.38312;

    const double  TO_RAD = 3.14159/180;
    const double  TO_DEG = 180/3.14159;

    void optionsFunc(char &is, bool &ci);
    void selectProgFunc();

#endif // FUNC_H
