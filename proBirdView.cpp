#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lib_misc.h"
#include "lib_math.h"
#include "proBirdView.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;
//-------------------------------------------------------

Mat translateImg(Mat &img, int offsetx, int offsety){
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img,img,trans_mat,img.size());
    return trans_mat;
}

void birdView(const string name_ori)
{
    //Rotation Matrix
    double alpha(0), beta(0), gamma(0);  //All angles are initialized as zero.
    beta = -30*TO_RAD;
    Mat R_pitch = (Mat_<double>(3, 3) << 1,  0,         0,
                                         0,  cos(beta), sin(beta),
                                         0, -sin(beta), cos(beta));
    Mat R_yaw   = (Mat_<double>(3, 3) << cos(alpha), 0, -sin(alpha),
                                         0,          1, 0,
                                         sin(alpha), 0, cos(alpha));
    Mat R_roll  = (Mat_<double>(3, 3) << cos(gamma) , sin(gamma), 0,
                                         -sin(gamma), cos(gamma), 0,
                                         0,           0,          1);
    Mat R = R_roll*R_yaw*R_pitch;
    //cout << "R" << R << endl;

    //Homography matrix.
    Mat H = K*R*K.inv();

    //Create the birdView image.
    Mat img_ori, img_transformed;
    img_ori = imread(name_ori, CV_LOAD_IMAGE_COLOR);   // Read the file
    if( !img_ori.data)   {                             // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {
        string nameBirdView = "Bird View";
        warpPerspective(img_ori, img_transformed, H, Size(800, 1600));

        //translateImg(img_transformed,0,-200);

        namedWindow( nameBirdView, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO );
        imshow( nameBirdView, img_transformed );

        waitKey(0);
        destroyAllWindows();
    }
}

void proBirdView()
{
    //Let the user to input the file name.
    cout << "=> Input the name of the original image." << endl;
    string name_ori;
    cin >> name_ori;

    //Start to convert the birdView image
    birdView(name_ori);
}

