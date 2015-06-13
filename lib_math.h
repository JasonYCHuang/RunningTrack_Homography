#ifndef LIB_MATH_H
#define LIB_MATH_H

#include "lib_misc.h"

using namespace cv;
using namespace std;

// Declare functions
double  calcDivision(const double numerator, const double denominator);
Mat     getRotationMatrix(double alpha, double beta, double gamma);
double  getMax(const double a, const double b);
double  getMin(const double a, const double b);
double  calcSlope(Point2f pt1, Point2f pt2);
double  calcIntersect(Point2f pt1, Point2f pt2);
Mat     calcVanPts(Mat &src,  const vector<Point2f> pts, string name);
void    calcRotAngle(const Mat &unit_vector, double &pitch_deg, double &yaw_deg);

#endif // LIB_MATH_H
