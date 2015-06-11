#ifndef LINE2D_H
#define LINE2D_H

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

class Line2D
{
    // Private functions which are defined outside of this class.
    friend double calcSlope(Point2f pt1, Point2f pt2);
    friend double calcIntersect(Point2f pt1, Point2f pt2);

public:
    // Constructor.
    Line2D();
    Line2D(const Point2f pt1, const Point2f pt2);
    Line2D(const Point2f pt1, const Point2f pt2, const int lambda);
    // Destructor.
    ~Line2D ();

    void setLineParam(Point2f pt1, Point2f pt2, int lambda);

    Mat vect();     // Return the vector of the line.
    Point2f lVec(); // Return the vector of the line.

    // ax+by+lamb=0
    double a();     // Return the value of "a", which is normalized_a.
    double b();     // Return the value of "b", which is normalized_b.
    double lamb();  // Return the value of "lamb".

private:
    // y=mx+d, m=slope, d=intercept
    double  slope;
    double  intercept;

    // when Normalized, c=1, ax+by+1=0. // lineVector=[a, b, 1]
    double  normalized_a;
    double  normalized_b;
    int     lambda;
    Mat     lineVector;     // ax+by+c=0 => lineVector=[a, b, c]
};

#endif // LINE2D_H
