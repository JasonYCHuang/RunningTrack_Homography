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

Point2f calcVanPtsFunc(Mat &src,  const vector<Point2f> pts, string name)
{
    int num_pts = pts.size();
    //=====Calc and draw lines=====
    double m[2], b[2];     // y = mx+b
    for(int i = 0; i<num_pts; i+=2)
    {
        int beg_pts = i, end_pts = i+1;
        drawLineFunc( src, pts[beg_pts] , pts[end_pts], 'G');
        imshow( name, src );
        m[i/2] = slopeFunc(pts[beg_pts], pts[end_pts]);
        b[i/2] = intersectFunc(pts[beg_pts], pts[end_pts]);
    } // need to protect divided by 0  TBD
    //=====Calc vanishing point=====
    Point2f vanishing_pts;
    vanishing_pts.x = (b[1]-b[0])/(m[0]-m[1]);
    vanishing_pts.y = (b[1]*m[0]-b[0]*m[1])/(m[0]-m[1]);

    drawLineFunc( src, pts[1] ,vanishing_pts, 'Y');
    drawLineFunc( src, pts[2] ,vanishing_pts, 'R');
    imshow( name, src);

    return vanishing_pts;
}

void calcRotAngleFunc(const Mat &unit_vector, double &pitch, double &yaw)
{
    Mat u_d1 = unit_vector.clone();
    pitch = asin(-u_d1.at<double>(1,0))*TO_DEG;
    double tmp_y = u_d1.at<double>(2,0)/cos(pitch*TO_RAD);
    yaw = acos(tmp_y)*TO_DEG;
}




//----Legacy function, useless now--------
double calcProjAngleFunc(const Mat &direction1, const Mat &direction2, const char s)  //useless, kept as backup.
{
    Mat d1 = direction1.clone();
    Mat d2 = direction2.clone();
    switch (s) {
        case 'P':
            d1.row(0) = 0.0;
            d2.row(0) = 0.0;
            break;
        case 'Y':
            d1.row(1) = 0.0;
            d2.row(1) = 0.0;
            break;
        case 'R':
            d1.row(2) = 0.0;
            d2.row(2) = 0.0;
            break;
        default:
            break;
    }
    double cos_angle = d1.dot(d2)/norm(d1)/norm(d2);
    double angle = acos(cos_angle)*TO_DEG;
    return angle;
}
