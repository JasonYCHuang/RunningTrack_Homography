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


int main(int argc, char* argv[])
{
     //selectProgFunc();   //TBD

    //=====Loading image=====
    if( argc != 3)  {
        cout << "<Incorrect Usage>  valid input should be .\\RunningTrack 1st.jpg 2nd.jpg" << endl;
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

    Mat img_transformed, homography_matrix;

    hgTransformFunc(img_painted_1,img_painted_2, img_transformed, homography_matrix, name_1, name_2);

    string name_transformed = "The transformed image";
    namedWindow( name_transformed, WINDOW_AUTOSIZE );
    imshow( name_transformed, img_transformed );

    waitKey(0);

    imwrite( "./HT_OriImg.jpg", img_painted_1 );
    imwrite( "./HT_RefImg.jpg", img_painted_2 );
    imwrite( "./HT_TransImg.jpg", img_transformed );



    return 0;
}














/*

Mat mapping_matrix = (Mat_<double>(8,8) << pts_vertx_1[0].x, pts_vertx_1[0].y ,1, 0, 0, 0, -1*pts_vertx_1[0].x*ideal_pts[0].x, -1*pts_vertx_1[0].y*ideal_pts[0].x,
                                           0, 0, 0, pts_vertx_1[0].x, pts_vertx_1[0].y ,1, -1*pts_vertx_1[0].x*ideal_pts[0].y, -1*pts_vertx_1[0].y*ideal_pts[0].y,
                                           pts_vertx_1[1].x, pts_vertx_1[1].y ,1, 0, 0, 0, -1*pts_vertx_1[1].x*ideal_pts[1].x, -1*pts_vertx_1[1].y*ideal_pts[1].x,
                                           0, 0, 0, pts_vertx_1[1].x, pts_vertx_1[1].y ,1, -1*pts_vertx_1[1].x*ideal_pts[1].y, -1*pts_vertx_1[1].y*ideal_pts[1].y,
                                           pts_vertx_1[2].x, pts_vertx_1[2].y ,1, 0, 0, 0, -1*pts_vertx_1[2].x*ideal_pts[2].x, -1*pts_vertx_1[2].y*ideal_pts[2].x,
                                           0, 0, 0, pts_vertx_1[2].x, pts_vertx_1[2].y ,1, -1*pts_vertx_1[2].x*ideal_pts[2].y, -1*pts_vertx_1[2].y*ideal_pts[2].y,
                                           pts_vertx_1[3].x, pts_vertx_1[3].y ,1, 0, 0, 0, -1*pts_vertx_1[3].x*ideal_pts[3].x, -1*pts_vertx_1[3].y*ideal_pts[3].x,
                                           0, 0, 0, pts_vertx_1[3].x, pts_vertx_1[3].y ,1, -1*pts_vertx_1[3].x*ideal_pts[3].y, -1*pts_vertx_1[3].y*ideal_pts[3].y  );
Mat inv_mapping_matrix, transformation_params;
Mat ideal_pt_matrix = (Mat_<double>(8,1) << ideal_pts[0].x, ideal_pts[0].y, ideal_pts[1].x, ideal_pts[1].y, ideal_pts[2].x, ideal_pts[2].y, ideal_pts[3].x, ideal_pts[3].y);
invert(mapping_matrix, inv_mapping_matrix);
transformation_params = inv_mapping_matrix*ideal_pt_matrix;
Mat transformation_matrix = (Mat_<double>(3,3) << transformation_params.at<double>(0,0), transformation_params.at<double>(1,0), transformation_params.at<double>(2,0),
                                                   transformation_params.at<double>(3,0), transformation_params.at<double>(4,0), transformation_params.at<double>(5,0),
                                                   transformation_params.at<double>(6,0), transformation_params.at<double>(7,0), 1 );

                                                   */
