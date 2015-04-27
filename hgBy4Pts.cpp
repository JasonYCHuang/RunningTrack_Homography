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

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;
//-------------------------------------------------------


void get4RandPts(Mat &img, vector<Point2f> &pts, const string name )
{
    imshow( name, img );                   // Show image.
    for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Get points=====
        setMouseCallback( name, onMouseFunc, (void*) &*it );   // solve "iterator can not be converted to void*"
        waitKey(0);
        drawCircleFunc( img, *it, 'B' );
        imshow( name, img );
    }
    for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Draw lines=====
        auto next = it+1 != pts.end() ? it+1 : pts.begin();
        drawLineFunc( img, *it , *next, 'G');
        imshow( name, img );
    }
}

void hgTransformFunc(Mat &ori, Mat &ref, Mat &target, Mat &h_matrix, const string n1, const string n2)
{
    int i = 4;   //get 4 pts
    vector<Point2f> pts_vertx_ori(i), pts_vertx_ref(i);
    get4RandPts(ori, pts_vertx_ori, n1);
    get4RandPts(ref, pts_vertx_ref, n2);

    h_matrix = findHomography(pts_vertx_ori, pts_vertx_ref, 0);

    warpPerspective(ori, target, h_matrix, target.size());

    imgRotateFunc(target, target, 0);
}



void hgTransBy4RandPtsFunc(const string name_ori, const string name_ref)
{
    Mat img_ori, img_ref;
    img_ori = imread(name_ori, CV_LOAD_IMAGE_COLOR);   // Read the 1st file
    img_ref = imread(name_ref, CV_LOAD_IMAGE_COLOR);   // Read the 2nd file
    if( !img_ori.data || !img_ref.data)   {         // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {
        //=====Display 1st image=====
        Mat img_painted_ori = img_ori.clone();          // img_painted & img_original are independent.
        namedWindow( name_ori, WINDOW_AUTOSIZE );      // Create a window for display.

        //=====Display 2nd image=====
        Mat img_painted_ref = img_ref.clone();          // img_painted & img_original are independent.
        namedWindow( name_ref, WINDOW_AUTOSIZE );      // Create a window for display.

        Mat img_transformed, homography_matrix;
        hgTransformFunc(img_painted_ori,img_painted_ref, img_transformed, homography_matrix, name_ori, name_ref);

        string name_transformed = "The transformed image";
        namedWindow( name_transformed, WINDOW_AUTOSIZE );
        imshow( name_transformed, img_transformed );

        imwrite( "./HT_OriImg.jpg", img_painted_ori );
        imwrite( "./HT_RefImg.jpg", img_painted_ref );
        imwrite( "./HT_TransImg.jpg", img_transformed );

        waitKey(0);

        destroyAllWindows();
    }
}

void projectHgTra4Pts()
{
    string name_ori, name_ref;
    cout << "=> Input the name of the original image." << endl;
    cin >> name_ori;
    cout << "=> Input the name of the reference image." << endl;
    cin >> name_ref;
    hgTransBy4RandPtsFunc(name_ori, name_ref);
    cout << endl << endl << endl;
}

