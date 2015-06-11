#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lib_misc.h"
#include "lib_math.h"
#include "proHgBy4Pts.h"
#include "proRotByVanPts.h"
#include "line2D.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

Line2D::Line2D()
{
    // y=mx+d
    slope = 0.0;
    intercept = 0.0;
    lineVector = (Mat_<double>(3,1) << 0, 1, 0);    // Default initialized as y=0.
}

Line2D::Line2D(const Point2f pt1, const Point2f pt2)
{
    slope = calcSlope(pt1, pt2);
    intercept = calcIntersect(pt1, pt2);
    // y=mx+d => mx-y+d=0 => ax+by+c=0
    lineVector = (Mat_<double>(3,1) << slope, -1, intercept);   // m=slope, d=intercept // lineVector=[a, b, c]
}


Line2D::Line2D(const Point2f pt1, const Point2f pt2, const int lambda)
{
    slope = calcSlope(pt1, pt2);
    intercept = calcIntersect(pt1, pt2);
    // y=mx+d => mx-y+d=0 => ax+by+c=0
    lineVector = (Mat_<double>(3,1) << slope, -1, intercept);   // m=slope, d=intercept // lineVector=[a, b, c]
    lambda = lambda;
}


void Line2D::setLineParam(const Point2f pt1, const Point2f pt2, const int lambda)
{
    slope = calcSlope(pt1, pt2);
    intercept = calcIntersect(pt1, pt2);

    // y=mx+d => mx-y+d=0 => ax+by+c=0
    lineVector = (Mat_<double>(3,1) << slope, -1, intercept);   // m=slope, d=intercept // lineVector=[a, b, c]

    // Normalized: ax+by+1=0, c=1, lineVector=[a, b, 1]
    normalized_a = slope/intercept;
    normalized_b = -1/intercept;
    lambda = lambda;
}

Mat Line2D::vect()
{
    return lineVector;
}

double Line2D::a()
{
    return normalized_a;
}

double Line2D::b()
{
    return normalized_b;
}

double Line2D::lamb()
{
    return lambda;
}
