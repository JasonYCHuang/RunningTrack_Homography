#ifndef LIB_MATH_H
#define LIB_MATH_H

#include "lib_misc.h"
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

// Define namespace constants
namespace constant
{
    const double PI = 3.14159265358979;
    const double  TO_RAD = PI/180;
    const double  TO_DEG = 180/PI;
}

double  calcDivision(const double numerator, const double denominator);
Mat     getRotationMatrix(double alpha, double beta, double gamma);
double  getMax(const double a, const double b);
double  getMin(const double a, const double b);
double  calcSlope(Point2f pt1, Point2f pt2);
double  calcIntersect(Point2f pt1, Point2f pt2);
Mat     calcVanPts(Mat &src,  const vector<Point2f> pts, string name);
void    calcRotAngle(const Mat &unit_vector, double &pitch_deg, double &yaw_deg);

//----Legacy function, useless now--------
double  calcProjAngle(const Mat &direction1, const Mat &direction2, const char s);
Mat     calcCurl(const Mat &m1, const Mat &m2);

#endif // LIB_MATH_H
