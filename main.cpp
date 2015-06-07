#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

#include "lib_misc.h"
#include "lib_math.h"
#include "proHgBy4Pts.h"
#include "proHgByFeatures.h"
#include "proRotByVanPts.h"
#include "proVanLine.h"
#include "proBirdView.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif


//
//Welcome message for users to select functions.
//
char optionsFunc(bool &ci)
{
    if (ci)     {
        cout << "---------------------------------------------------------------" << endl;
        cout << "[1] Homography transformation from 4-random-points of 2 images." << endl;
        cout << "[2] Homography transformation from 4-vertex to fit into a rectangle." << endl;
        cout << "[3] Homography transformation of lines." << endl;
        cout << "[4] Rotation matrix from vanishing points." << endl;
        cout << "[5] Get roll angle from a vanishing line." << endl;
        cout << "[6] Homography transformation from feature points" << endl;
        cout << "[7] Get the birdView image" << endl;
        cout << "-----Input a number or '0' to terminate the program-----" << endl;
    }
    else    {
        ci = true;
    }
    char is;
    cin >> is;

    return is;
}


//
//Main
//
int main()
{
    char prog_select = '0';
    bool brk_token = false, valid_input = true;

    while(!brk_token)    {
        prog_select = optionsFunc(valid_input);
        switch (prog_select) {
            case '1':
                projectHgTra4Pts();
                break;
            case '2':
                cout << "TBD!" << endl;
                break;
            case '3':
                cout << "TBD!" << endl;
                break;
            case '4':
                projectRotByVanPts();
                break;
            case '5':
                projectVanLine();
                break;
            case '6':
                projectHgByFeatures();
                break;
            case '7':
                proBirdView();
                break;
            case '0':
                cout << "See You Next Time!!" << endl;
                brk_token = true;   // terminate the program.
                break;
            default:
                cout << endl << endl << "<Invalid input!>" << endl;
                valid_input = false;
                break;
        }
    }

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
