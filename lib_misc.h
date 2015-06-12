#ifndef LIB_MISC_H
#define LIB_MISC_H

#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------------------------------
Scalar colorVect(char color_name);
void drawCircle(Mat &img, Point center, char color );           //TBD
void drawLine(Mat &img, Point2f pt1, Point2f pt2, char color ); //TBD
void drawCenter(Mat &src);                                      //TBD
void onMouse(int event, int x, int y, int , void* user_data);
void imgRotate(Mat &src, Mat &dst, double angle);
void getPtsLoc(Mat &img, vector<Point2f> &pts, const string name );

#endif // LIB_MISC_H
