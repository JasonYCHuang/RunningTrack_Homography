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
    Point2f pt1(1, 1), pt2(2, 1);   // Default initialization.
    setLineParams(pt1, pt2, 0);
}

Line2D::Line2D(const Point2f pt1, const Point2f pt2)
{
    setLineParams(pt1, pt2, 0);
}


Line2D::Line2D(const Point2f pt1, const Point2f pt2, const int lambda_group)
{
    setLineParams(pt1, pt2, lambda_group);
}


void Line2D::setLineParams(const Point2f pt1, const Point2f pt2, const int lambda_group)
{
    // Calculate slope and intercept.
    slope = calcSlope(pt1, pt2);
    intercept = calcIntersect(pt1, pt2);

    // Normalized: ax+by+1=0, c=1, lineVector=[normalized_a, normalized_b, 1]
    normalized_a = calcDivision( slope, intercept );
    normalized_b = calcDivision( -1, intercept);        // TBD: divided by zero.

    // Get line vector=[a, b, 1].     // y=mx+d => mx-y+d=0 => ax+by+c=0 => normalized_a*x+normalized_b*y=1
    lineVector = (Mat_<double>(3,1) << normalized_a, normalized_b, 1);

    // For parallel lines, ax+by+lambda=0, lambda=continuous integer.
    lambda = lambda_group;      // If we don' consider parallel lines, lambda will be set as 0.
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
