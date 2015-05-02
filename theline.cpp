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
#include "theline.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

TheLine::TheLine()
{
    _slope = 0.0;
    _intercept = 0.0;
    _lineVector = (Mat_<double>(3,1) << 0, 0, 0);
}

TheLine::TheLine(const Point2f pt1, const Point2f pt2)
{
    _slope = calcSlopeFunc(pt1, pt2);
    _intercept = calcIntersectFunc(pt1, pt2);
    _lineVector = (Mat_<double>(3,1) << _slope/_intercept, -1/_intercept, _intercept/_intercept);
    // y = mx + t  => ax + by + c = 0, set c = 1, a line vector is scalible, i.e. v & k*v is the same line. k is a const.
}

void TheLine::setLineParam(const Point2f pt1, const Point2f pt2)
{
    _slope = calcSlopeFunc(pt1, pt2);
    _intercept = calcIntersectFunc(pt1, pt2);
    _lineVector = (Mat_<double>(3,1) << _slope/_intercept, -1/_intercept, _intercept/_intercept);
}

Mat TheLine::vect()
{
    return _lineVector;
}
