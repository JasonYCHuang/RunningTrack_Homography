#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lib_misc.h"
#include "lib_math.h"
#include "proHgBy4Pts.h"
#include "proRotByVanPts.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;
//-------------------------------------------------------

void rotByVarPtsFunc(const string name)
{
    Mat img;
    img = imread(name, CV_LOAD_IMAGE_COLOR);   // Read the 1st file

    if( !img.data)   {         // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {










/*
        //=====Draw center=====
        drawCenterFunc(img);

        //=====Calc vanishing point & Set homo coordinate=====
        vector<Point2f> selected_pts(4);
        getPtsLocFunc(img, selected_pts, name);
        Point2f vanish_pts_ori = calcVanPtsFunc(img, selected_pts, name);

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
        d_ori = d_ori/norm(d_ori);           //get unit vector
        d_center = d_center/norm(d_center);
        cout << d_ori << endl;
        cout << d_center << endl;
        Mat v = d_ori.cross(d_center);
        double s = norm(v);
        double c = d_ori.dot(d_center);

        Mat vx =  (Mat_<double>(3,3) <<    0,                   -v.at<double>(2,0),  v.at<double>(1,0),
                                           v.at<double>(2,0),   0,                  -v.at<double>(0,0),
                                          -v.at<double>(1,0),   v.at<double>(0,0),   0                 );

        cout << "vx = " << vx << endl;
        cout << "s = " << s << endl;
        cout << "c = " << c << endl;


        Mat Rot_matrix = Mat::eye(3, 3, CV_32F); // + vx ; //+ vx*vx*(1-c)/s/s;


        cout << Rot_matrix << endl;
*/





        /*

        //=====Pitch, Yaw, Roll======================
        double pitch_angle, yaw_angle;
        calcRotAngleFunc(d_ori, pitch_angle, yaw_angle);   //calc angle from rotation matrix.

        cout << "Assume roll = 0(deg)" << endl;
        cout << "pitch_angle = " << pitch_angle << "(deg)" << endl;
        cout << "yaw_angle   = " << yaw_angle   << "(deg)" << endl;

        cout << "====================================" << endl;
        cout << d_ori << endl;


        */
        //imwrite( "./Rot.jpg", img );

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
    cout << endl << endl << endl;
}
