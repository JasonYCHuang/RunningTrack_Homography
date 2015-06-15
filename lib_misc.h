#ifndef LIB_MISC_H
#define LIB_MISC_H

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

// Define namespace constants
namespace constant
{
    const double  PI = 3.14159265358979;
    const double  TO_RAD = PI/180;
    const double  TO_DEG = 180/PI;
}

// Declare functions
Scalar  colorScalar(char color_name);
void    onMouse(int event, int x, int y, int , void* user_data);
void    imgRotate(Mat &src, Mat &dst, double angle);
void    getPtsLoc(Mat &img, vector<Point2f> &pts, const string name );

#endif // LIB_MISC_H
