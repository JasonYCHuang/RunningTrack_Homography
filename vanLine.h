#ifndef VANLINE_H
#define VANLINE_H

#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

extern const Point2f  CAM_CENTER;
extern const Point2f  IMG_CENTER;
extern const double  FOCUS_1;
extern const double  FOCUS_2;
extern const double  TO_RAD;
extern const double  TO_DEG;
//-------------------------------------------------------
void projectVanLine();

#endif // VANLINE_H
