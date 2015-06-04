#ifndef PROROTBYVANPTS_H
#define PROROTBYVANPTS_H

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
void rotByVarPtsFunc(const string name);
void projectRotByVanPts();

#endif // PROROTBYVANPTS_H
