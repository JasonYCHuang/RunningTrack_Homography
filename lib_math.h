#ifndef LIB_MATH_H
#define LIB_MATH_H

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
//-------------------------------------------------------
double slopeFunc(Point2f pt1, Point2f pt2);
double intersectFunc(Point2f pt1, Point2f pt2);
Point2f calcVanishingPts(Mat &src,  const vector<Point2f> pts, string name);
void calcRotAngleFunc(const Mat &unit_vector, double &pitch, double &yaw);

//----Legacy function, useless now--------
double calcProjAngleFunc(const Mat &direction1, const Mat &direction2, const char s);

#endif // LIB_MATH_H



