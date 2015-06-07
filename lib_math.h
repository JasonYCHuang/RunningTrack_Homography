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


const Point2f  CAM_CENTER(831, 388);
const Point2f  IMG_CENTER(831, 388);
const double  FOCUS_1 = 1000;
const double  FOCUS_2 = 1000;
/*
const double  FOCUS_1 = 801.08310;      //test
const double  FOCUS_2 = 805.38312;      //test
const Point2f  CAM_CENTER(442.21533, 284.83506);  //test
const Point2f  IMG_CENTER(442.21533, 284.83506);  //test
*/
const Point2f  V_TOP(442.21533, 0);
const Point2f  V_BOT(442.21533, 600);
const Point2f  H_LFT(0, 284.83506);
const Point2f  H_RIT(800, 284.83506);

const double  TO_RAD = 3.14159/180;
const double  TO_DEG = 180/3.14159;

//camera internal parameter
const Mat K = (Mat_<double>(3,3) << FOCUS_1, 0.00*FOCUS_1, CAM_CENTER.x,
                                    0,       FOCUS_2,      CAM_CENTER.y,
                                    0,       0,            1);

//-------------------------------------------------------
Mat getRotationMatrix(double alpha, double beta, double gamma);
double getMax(const double a, const double b);
double getMin(const double a, const double b);
double calcSlopeFunc(Point2f pt1, Point2f pt2);
double calcIntersectFunc(Point2f pt1, Point2f pt2);
Mat calcVanPtsFunc(Mat &src,  const vector<Point2f> pts, string name);
void calcRotAngleFunc(const Mat &unit_vector, double &pitch, double &yaw);


//----Legacy function, useless now--------
double calcProjAngleFunc(const Mat &direction1, const Mat &direction2, const char s);
Mat calcCurlFunc(const Mat &m1, const Mat &m2);


#endif // LIB_MATH_H



