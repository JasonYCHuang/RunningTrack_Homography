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
    TheLine(Point2f pt1, Point2f pt2, int lambda);

    void setLineParam(Point2f pt1, Point2f pt2, int lambda);

    Mat vect();   //yield the vector of the line.
    Point2f lVec();

    double a();
    double b();
    double lamb();

private:
    double _slope;
    double _intercept;
    double _normal_a;
    double _normal_b;
    int _lambda;
    Mat _lineVector;
};

#endif // THELINE_H
