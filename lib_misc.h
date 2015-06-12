#ifndef LIB_MISC_H
#define LIB_MISC_H

#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------------------------------
Scalar colorVectFunc(char color_name);
void drawCircleFunc(Mat &img, Point center, char color );           //TBD
void drawLineFunc(Mat &img, Point2f pt1, Point2f pt2, char color ); //TBD
void drawCenterFunc(Mat &src);                                      //TBD
void onMouseFunc(int event, int x, int y, int , void* user_data);
void imgRotateFunc(Mat &src, Mat &dst, double angle);
void getPtsLocFunc(Mat &img, vector<Point2f> &pts, const string name );

#endif // LIB_MISC_H
