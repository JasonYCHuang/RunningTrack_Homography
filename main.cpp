#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "func1.h"
#include "func2.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

void get4RandPts(Mat &img, Vector<Point2f> &pts, const string name )
{
    imshow( name, img );                   // Show image.
    for(auto it = pts.begin(); it != pts.end(); ++it)
    {
        setMouseCallback( name, onMouseFunc, (void*)it);
        waitKey(0);
        drawCircleFunc( img, *it, 'B' );
        imshow( name, img );
    }
}










int main(int argc, char* argv[])
{
     //selectProgFunc();   //TBD


    //=====Loading image=====
    if( argc != 3)  {
        cout << "<Incorrect Usage>  valid input should be .\RunningTrack 1st.jpg 2nd.jpg" << endl;
        return -1;
    }

    Mat img_ori_1, img_ori_2;
    img_ori_1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the 1st file
    img_ori_2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);   // Read the 2nd file
    if( !img_ori_1.data || !img_ori_2.data)   {         // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
        return -1;
    }

    //=====Display 1st image=====
    string name_1 = "The 1st image";
    Mat img_painted_1 = img_ori_1.clone();          // img_painted & img_original are independent.
    namedWindow( name_1, WINDOW_AUTOSIZE );      // Create a window for display.

    //=====Display 2nd image=====
    string name_2 = "The 2nd image";
    Mat img_painted_2 = img_ori_2.clone();          // img_painted & img_original are independent.
    namedWindow( name_2, WINDOW_AUTOSIZE );      // Create a window for display.

    //=====Get points by mouse clicking=====
    int i = 4;
    Vector<Point2f> pts_vertx_1(i), pts_vertx_2(i);
    get4RandPts(img_painted_1, pts_vertx_1, name_1 );
    get4RandPts(img_painted_2, pts_vertx_2, name_2 );





    /*











    //=====Draw lines=====
    for(i = 0; i<4; i++)
    {
        int end_pt_num = i==3 ? 0 : i+1;
        drawLineFunc( img_painted, selected_pts[i] , selected_pts[end_pt_num], 'G');
        imshow( name_img, img_painted );
    }

    waitKey(0);                                          // Wait for a keystroke in the window

    //======Define Target points=======
    Point2f ideal_pts[4];
    ideal_pts[0] =  Point2f(0, 0);
    ideal_pts[1] =  Point2f(80, 0);
    ideal_pts[2] =  Point2f(80, 50);
    ideal_pts[3] =  Point2f(0, 50);

    //======Calc transformation_matrix=======
    //Mat transformation_matrix;
    //transformation_matrix = getPerspectiveTransform(selected_pts, ideal_pts);
    //cout << "transformation_matrix" << endl << transformation_matrix << endl;

    Mat mapping_matrix = (Mat_<double>(8,8) << selected_pts[0].x, selected_pts[0].y ,1, 0, 0, 0, -1*selected_pts[0].x*ideal_pts[0].x, -1*selected_pts[0].y*ideal_pts[0].x,
                                               0, 0, 0, selected_pts[0].x, selected_pts[0].y ,1, -1*selected_pts[0].x*ideal_pts[0].y, -1*selected_pts[0].y*ideal_pts[0].y,
                                               selected_pts[1].x, selected_pts[1].y ,1, 0, 0, 0, -1*selected_pts[1].x*ideal_pts[1].x, -1*selected_pts[1].y*ideal_pts[1].x,
                                               0, 0, 0, selected_pts[1].x, selected_pts[1].y ,1, -1*selected_pts[1].x*ideal_pts[1].y, -1*selected_pts[1].y*ideal_pts[1].y,
                                               selected_pts[2].x, selected_pts[2].y ,1, 0, 0, 0, -1*selected_pts[2].x*ideal_pts[2].x, -1*selected_pts[2].y*ideal_pts[2].x,
                                               0, 0, 0, selected_pts[2].x, selected_pts[2].y ,1, -1*selected_pts[2].x*ideal_pts[2].y, -1*selected_pts[2].y*ideal_pts[2].y,
                                               selected_pts[3].x, selected_pts[3].y ,1, 0, 0, 0, -1*selected_pts[3].x*ideal_pts[3].x, -1*selected_pts[3].y*ideal_pts[3].x,
                                               0, 0, 0, selected_pts[3].x, selected_pts[3].y ,1, -1*selected_pts[3].x*ideal_pts[3].y, -1*selected_pts[3].y*ideal_pts[3].y  );
    Mat inv_mapping_matrix, transformation_params;
    Mat ideal_pt_matrix = (Mat_<double>(8,1) << ideal_pts[0].x, ideal_pts[0].y, ideal_pts[1].x, ideal_pts[1].y, ideal_pts[2].x, ideal_pts[2].y, ideal_pts[3].x, ideal_pts[3].y);
    invert(mapping_matrix, inv_mapping_matrix);
    transformation_params = inv_mapping_matrix*ideal_pt_matrix;
    Mat transformation_matrix = (Mat_<double>(3,3) << transformation_params.at<double>(0,0), transformation_params.at<double>(1,0), transformation_params.at<double>(2,0),
                                                       transformation_params.at<double>(3,0), transformation_params.at<double>(4,0), transformation_params.at<double>(5,0),
                                                       transformation_params.at<double>(6,0), transformation_params.at<double>(7,0), 1 );

    //======Draw Bird view image and rotate it=======
    Mat img_transformed;
    warpPerspective(img_painted, img_transformed, transformation_matrix, img_painted.size());

    Mat img_trans_rotated;
    imgRotateFunc(img_transformed, img_trans_rotated, 90);

    string name_img_trans_rotated = "Bird view image";
    namedWindow( name_img_trans_rotated, CV_WINDOW_KEEPRATIO );
    imshow( name_img_trans_rotated, img_trans_rotated );

    waitKey(0);

    imwrite( "./OriginalImg.jpg", img_painted );
    imwrite( "./BirdViewImg.jpg", img_trans_rotated );

    */

    return 0;
}
