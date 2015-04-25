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

int main(int argc, char* argv[])
{
    selectProgFunc();   //TBD




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
