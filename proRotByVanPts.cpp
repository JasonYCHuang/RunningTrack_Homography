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
    img = imread(name, CV_LOAD_IMAGE_COLOR);   // Read the file
    if( !img.data)   {         // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {
        // Draw the camera center
        drawCenter(img);

        // Calculate the vanishing point by 4 manual selected pts & Set homogeneous coordinate
        vector<Point2f> selected_pts(4);
        getPtsLoc(img, selected_pts, name);
        Mat v_track_line    = calcVanPts(img, selected_pts, name);      //location of the vanishing point on the image.
        Mat v_camera_center = (Mat_<double>(3, 1) << CAM_CENTER.x, CAM_CENTER.y, 1); //location of the camera center on the image.

        // Camera internal parameter
        Mat inv_K;
        invert(K, inv_K);

        // v=Kd     // a vanishing point "v" back-projects to a ray with direction d.
        Mat d_track_line    = inv_K*v_track_line;
        Mat d_camera_center = inv_K*v_camera_center;
        d_track_line = d_track_line/norm(d_track_line);           //normalized as a unit vector
        d_camera_center = d_camera_center/norm(d_camera_center);  //normalized as a unit vector
        // //cout << d_track_line << endl;
        // //cout << d_camera_center << endl;

        // Calculate the angle between the 2 vectors. [1]sport track lines direction. [2]camera center pointing direction.
        Mat v = d_track_line.cross(d_camera_center);      // v = A.cross(B) = |A|*|B|*sin(theta)
        double sin = norm(v);                             // Since d_track_line and d_camera_center are unit vectors, xross magnitude is equal to sin.
        double cos = d_track_line.dot(d_camera_center);       // Since d_track_line and d_camera_center are unit vectors, dot magnitude is equal to cos.

        Mat vx =  (Mat_<double>(3,3) <<    0,                   -v.at<double>(2,0),  v.at<double>(1,0),
                                           v.at<double>(2,0),   0,                  -v.at<double>(0,0),
                                          -v.at<double>(1,0),   v.at<double>(0,0),   0                 );

        cout << "vx = " << vx << endl;
        cout << "sin = " << sin << endl;
        cout << "cos = " << cos << endl;

        Mat R = Mat::eye(3, 3, CV_64F) + vx + vx*vx*((1-cos)/(sin*sin));   //http://math.stackexchange.com/questions/180418/calculate-rotation-matrix-to-align-vector-a-to-vector-b-in-3d
        cout << R << endl;
        cout << "pitch = " << atan(R.at<double>(1, 2) / R.at<double>(2,2))*constant::TO_DEG << endl;
        cout << "yaw = "   << -asin(R.at<double>(0, 2))*constant::TO_DEG << endl;
        cout << "-------------------" << endl;

        cout << "pitch = " << asin(R.at<double>(1, 2))*constant::TO_DEG << endl;
        cout << "yaw = "   << -atan(R.at<double>(0, 2) / R.at<double>(2,2))*constant::TO_DEG << endl;
        cout << "-------------------" << endl;

        // Calculate Pitch, Yaw angles base on Roll=0.
        double pitch, yaw;
        calcRotAngle(d_track_line, pitch, yaw);   //calc angle from rotation matrix.
        cout << "Assume roll = 0(deg)" << endl;
        cout << "pitch_angle = " << pitch << "(deg)" << endl;
        cout << "yaw_angle   = " << yaw   << "(deg)" << endl;


        imwrite( "./vPoint.jpg", img );

        waitKey(0);
        destroyAllWindows();
    }
}


void projectRotByVanPts()
{
    // Let the user to input the file name.
    string name_ori;
    cout << "=> Input the name of the original image." << endl;
    cin >> name_ori;

    // Start to calculate the vanishing point.
    rotByVarPtsFunc(name_ori);
    cout << endl << endl << endl;
}
