#ifndef LIB_MATH_H
#define LIB_MATH_H

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
Mat     calcVanPtsFunc(Mat &src,  const vector<Point2f> pts, string name);
void    calcRotAngleFunc(const Mat &unit_vector, double &pitch, double &yaw);


// TBD ----------------------------------------------------------
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

//camera internal parameter
const Mat K = (Mat_<double>(3,3) << FOCUS_1, 0.00*FOCUS_1, CAM_CENTER.x,
                                    0,       FOCUS_2,      CAM_CENTER.y,
                                    0,       0,            1);





//----Legacy function, useless now--------
double  calcProjAngleFunc(const Mat &direction1, const Mat &direction2, const char s);
Mat     calcCurlFunc(const Mat &m1, const Mat &m2);

#endif // LIB_MATH_H
