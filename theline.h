#ifndef THELINE_H
#define THELINE_H

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

class TheLine
{
    friend double slopeFunc(Point2f pt1, Point2f pt2);
    friend double intersectFunc(Point2f pt1, Point2f pt2);

public:
    TheLine();
    TheLine(Point2f pt1, Point2f pt2);

    void setLineParam(Point2f pt1, Point2f pt2);

    Mat vect();






private:
    double _slope;
    double _intercept;
    Mat _lineVector;
};

#endif // THELINE_H
