#ifndef LINE2D_H
#define LINE2D_H

#include "lib_misc.h"
#include "lib_math.h"

using namespace cv;
using namespace std;

class Line2D
{
    // Set global functions which can access private parts of this class.
    friend double calcSlope(Point2f pt1, Point2f pt2);
    friend double calcIntersect(Point2f pt1, Point2f pt2);

public:
    // Constructor.
    Line2D();
    Line2D(const Point2f pt1, const Point2f pt2);
    Line2D(const Point2f pt1, const Point2f pt2, const int lambda_group);  // lambda_group is for parallel lines case only.

    // Calculate parameters of the line.
    void setLineParams(const Point2f pt1, const Point2f pt2, const int lambda_group);

    // Return the vector of the line.
    Mat vect();     // [a, b, 1]

    // ax+by+lamb=0
    double a();     // Return the value of "a", which is normalized_a.
    double b();     // Return the value of "b", which is normalized_b.
    // lamb is for parallel lines case only.
    double lamb();  // Return the value of "lamb".

private:
    // y=mx+d, m=slope, d=intercept
    double  slope;          // m
    double  intercept;      // d

    // ax+by+1=0 => lineVector=[a, b, 1]
    Mat     line_vector;

    // when Normalized, c=1, ax+by+1=0. // lineVector=[a, b, 1]
    double  normalized_a;
    double  normalized_b;
    int     lambda;         // For parallel lines, ax+by+lambda=0, lambda=continuous integer.
                            // If we don' consider parallel lines, lambda will be set as 0.
};

#endif // LINE2D_H
