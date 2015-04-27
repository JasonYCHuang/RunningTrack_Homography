#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lib_misc.h"
#include "lib_math.h"
#include "hgBy4Pts.h"
#include "rotByVanPts.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

//-------------------------------------------------------
double slopeFunc(Point2f pt1, Point2f pt2)
{
    double slope;
    slope = (pt2.y - pt1.y)/(pt2.x - pt1.x);
    return slope;
}
double intersectFunc(Point2f pt1, Point2f pt2)
{
    double intersect;
    intersect = (pt2.x*pt1.y - pt1.x*pt2.y)/(pt2.x - pt1.x);
    return intersect;
}
