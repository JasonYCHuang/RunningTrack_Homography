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
map<string, double> getBoundary(const vector<Point2f> &corners)
{
    map<string, double> boundary;
    for(unsigned int j=0; j!=corners.size(); ++j)    {
        if(boundary.empty())    {      // Initialized boundary if there is no data.
            boundary["left"]   = corners[j].x;
            boundary["right"]  = corners[j].x;
            boundary["top"]    = corners[j].y;
            boundary["bottom"] = corners[j].y;
        } else  {                      // Compare corners to get the outer-most boundary.
            boundary["left"]   = getMin(boundary["left"], corners[j].x);
            boundary["right"]  = getMax(boundary["right"], corners[j].x);
            boundary["top"]    = getMin(boundary["top"], corners[j].y);
            boundary["bottom"] = getMax(boundary["bottom"], corners[j].y);
        }
    }
    // Calculate width and height
    boundary["width"]  = boundary["right"] - boundary["left"];
    boundary["height"] = boundary["bottom"] - boundary["top"];

    return boundary;
}

void birdView(const string name_ori)
{
    // Setting the rotation Matrix  // getRotationMatrix(yaw, pitch, roll)
    Mat R = getRotationMatrix(8.95887*constant::TO_RAD, (-6.65135-90)*constant::TO_RAD, 0);

    // Homography matrix calculated from pure rotation.
    Mat H = K*R*K.inv();

    // If the original image is valid, then create the birdView image.
    Mat img_ori, img_transformed;
    img_ori = imread(name_ori, CV_LOAD_IMAGE_COLOR);   // Read the file
    if( !img_ori.data)   {                             // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {
        // Calculate the amount to shift the image to field of view by corners.
        // Caution: This shift mechanism will be failure when the homography of the 4 corners swapped orders!
        vector<Mat> img_corners_coordinate{ (Mat_<double>(3, 1) << 0, 0, 1),
                                            (Mat_<double>(3, 1) << 0, img_ori.size().height, 1),
                                            (Mat_<double>(3, 1) << img_ori.size().width, img_ori.size().height, 1),
                                            (Mat_<double>(3, 1) << img_ori.size().width, 0, 1) };// The homogeneous coordinate of the original image.
        vector<Point2f> img_corners_transformed;    // Transformed image corners.
        for(auto &i : img_corners_coordinate)    {
            i = H*i;        // Homography transformation.
            img_corners_transformed.push_back(Point2f(i.at<double>(0, 0)/i.at<double>(2, 0), i.at<double>(1, 0)/i.at<double>(2, 0)));
            // //cout << "img_corners_transformed" << Point2f(i.at<double>(0, 0)/i.at<double>(2, 0), i.at<double>(1, 0)/i.at<double>(2, 0)) << endl;
        }
        map<string, double> boundary = getBoundary(img_corners_transformed);      // The boundary of transformed image corners.

        // Modify Homography Matrix to shift the image into the field of view.
        Mat shift = (Mat_<double>(3, 3) << 1, 0, -boundary["left"],
                                           0, 1, -boundary["top"]+6000,
                                           0, 0, 1);
        H = shift*H;    // Update Homography base on a shift, i.e. multiplied by a translation matrix.

        // Perspective transformation.
        warpPerspective(img_ori, img_transformed, H, Size(boundary["width"], boundary["height"]));

        // Display and save images
        string name_ori = "Original image";
        namedWindow( name_ori, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO );
        imshow( name_ori, img_ori );
        imwrite( "./original.jpg", img_ori );
        string name_bird_view = "Bird View";
        namedWindow( name_bird_view, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO );
        imshow( name_bird_view, img_transformed );
        imwrite( "./birdView.jpg", img_transformed );

        waitKey(0);
        destroyAllWindows();
    }
}

void proBirdView()
{
    // Let the user to input the file name.
    cout << "=> Input the name of the original image." << endl;
    string name_ori;
    cin >> name_ori;

    // Start to convert the birdView image
    birdView(name_ori);
}

