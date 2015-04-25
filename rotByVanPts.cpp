#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "func1.h"
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


Point2f getVanishingPts(Mat &src, string name )
{
    Mat img_painted = src.clone();               // img_painted & img_orig_1 are independent.
    namedWindow( name, WINDOW_AUTOSIZE );    // Create a window for display.
    imshow( name, src );                     // Show our image inside it.
    //=====Get points by mouse clicking=====
    int num_pts = 4, i;   //get 4 pts
    vector<Point2f> selected_pts(num_pts);
    get4RandPts(src, selected_pts, name );

    //=====Draw center=====
    drawCircleFunc( src, IMG_CENTER, 'M' );
    putText(src, "IMG_CENTER", IMG_CENTER, FONT_HERSHEY_PLAIN, 1, colorVectFunc('M'), 2, 8, false);
    drawCircleFunc( src, CAM_CENTER, 'R' );
    putText(src, "CAM_CENTER", CAM_CENTER, FONT_HERSHEY_PLAIN, 1, colorVectFunc('R'), 2, 8, false );
    //=====Draw and Calc lines=====
    double m[2], b[2];     // y = mx+b
    for(i = 0; i<num_pts; i+=2)
    {
        int beg_pts = i, end_pts = i+1;
        drawLineFunc( src, selected_pts[beg_pts] , selected_pts[end_pts], 'G');
        imshow( name, src );
        m[i/2] = slopeFunc(selected_pts[beg_pts], selected_pts[end_pts]);
        b[i/2] = intersectFunc(selected_pts[beg_pts], selected_pts[end_pts]);
    } // need to protect divided by 0  TBD
    //=====Calc vanishing point=====
    Point2f vanishing_pts;
    vanishing_pts.x = (b[1]-b[0])/(m[0]-m[1]);
    vanishing_pts.y = (b[1]*m[0]-b[0]*m[1])/(m[0]-m[1]);

    drawLineFunc( src, selected_pts[1] ,vanishing_pts, 'Y');
    drawLineFunc( src, selected_pts[2] ,vanishing_pts, 'R');
    imshow( name, src);

    return vanishing_pts;
}

double calcAngleFunc(const Mat &direction1, const Mat &direction2, const char s)
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
    double angle = acos(cos_angle)*180/3.14159;
    return angle;
}


void rotByVarPtsFunc(const string name)
{
    Mat img;
    img = imread(name, CV_LOAD_IMAGE_COLOR);   // Read the 1st file
    if( !img.data)   {         // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {
        //=====Calc vanishing point & Set homo coordinate=====
        Point2f vanish_pts_ori = getVanishingPts(img, name);
        Mat v_homo_coord_ori    = (Mat_<double>(3, 1) << vanish_pts_ori.x, vanish_pts_ori.y, 1);
        Mat v_homo_coord_center = (Mat_<double>(3, 1) << IMG_CENTER.x, IMG_CENTER.y, 1);

        //=====camera internal parameter=====
        Mat k_param = (Mat_<double>(3,3) << FOCUS_1, 0.00*FOCUS_1, CAM_CENTER.x,
                                            0,       FOCUS_2,      CAM_CENTER.y,
                                            0,       0,            1);
        Mat inv_k_param;
        invert(k_param, inv_k_param);
        Mat d_ori    = inv_k_param*v_homo_coord_ori;
        Mat d_center = inv_k_param*v_homo_coord_center;

        //=====Pitch, Yaw, Roll======================
        double pitch_angle = calcAngleFunc(d_ori, d_center, 'P');
        double yaw_angle   = calcAngleFunc(d_ori, d_center, 'Y');
        double roll_angle  = calcAngleFunc(d_ori, d_center, 'R');
        double std_angle   = calcAngleFunc(d_ori, d_center, 's');

        cout << "pitch_angle = " << pitch_angle << "(deg)" << endl;
        cout << "yaw_angle   = " << yaw_angle   << "(deg)" << endl;
        cout << "roll_angle  = " << roll_angle  << "(deg)" << endl;
        cout << "std_angle   = " << std_angle   << "(deg)" << endl;

        cout << "-----------ori-------------" << endl;
        cout << d_ori/norm(d_ori) << endl;
        cout << "-----------center-------------" << endl;
        cout << d_center << endl;

        imwrite( "./Rot.jpg", img );

        waitKey(0);
        destroyAllWindows();
    }
}


void projectRotByVanPts()
{
    string name_ori;
    cout << "=> Input the name of the original image." << endl;
    cin >> name_ori;
    rotByVarPtsFunc(name_ori);
}
