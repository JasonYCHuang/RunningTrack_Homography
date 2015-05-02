#ifndef PROHGBY4PTS_H
#define PROHGBY4PTS_H

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
//-------------------------------------------------------
void hgTransformFunc(Mat &ori, Mat &ref, Mat &target, Mat &h_matrix, const string n1, const string n2);
void hgTransBy4RandPtsFunc(const string name_ori, const string name_ref);
void projectHgTra4Pts();

#endif // PROHGBY4PTS_H
