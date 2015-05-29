#ifndef LIB_MISC_H
#define LIB_MISC_H

#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------------------------------
Scalar colorVectFunc(char color_name);
void drawCircleFunc(Mat &img, Point center, char color );
void drawLineFunc(Mat &img, Point2f pt1, Point2f pt2, char color );
void drawCenterFunc(Mat &src);
void onMouseFunc(int event, int x, int y, int , void* user_data);
void imgRotateFunc(Mat &src, Mat &dst, double angle);
void getPtsLocFunc(Mat &img, vector<Point2f> &pts, const string name );

#endif // LIB_MISC_H
