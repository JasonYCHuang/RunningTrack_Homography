#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lib_misc.h"
#include "hgBy4Pts.h"
#include "rotByVanPts.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;


//------------------------------------------------------------------------
Scalar colorVectFunc(char color_name)
{
    Scalar colorVector = Scalar( 0, 0, 0 );
    switch (color_name)   {
        case 'R' :
            colorVector = Scalar( 0, 0, 255 );
            break;
        case 'G' :
            colorVector = Scalar( 0, 255, 0 );
            break;
        case 'B' :
            colorVector = Scalar( 255, 0, 0 );
            break;
        case 'M' :
            colorVector = Scalar( 255, 0, 255 );
            break;
        case 'Y' :
            colorVector = Scalar( 0, 255, 255 );
            break;
        case 'K' :
            colorVector = Scalar( 0, 0, 0 );
            break;
    }
    return colorVector;
}



void drawCircleFunc( Mat &img, Point center, char color )
{
    int thickness = 2;
    int lineType = 8;
    circle(img, center, 5, colorVectFunc(color), thickness, lineType );
}

void drawLineFunc( Mat &img, Point2f pt1, Point2f pt2, char color )
{
    int thickness = 2;
    int lineType = 8;
    int lineShift = 0;

    line(img, pt1, pt2, colorVectFunc(color), thickness, lineType, lineShift );
}

void drawCenterFunc(Mat &src)
{
    drawCircleFunc( src, IMG_CENTER, 'M' );
    putText(src, "IMG_CENTER", IMG_CENTER, FONT_HERSHEY_PLAIN, 1, colorVectFunc('M'), 2, 8, false);
    drawCircleFunc( src, CAM_CENTER, 'R' );
    putText(src, "CAM_CENTER", CAM_CENTER, FONT_HERSHEY_PLAIN, 1, colorVectFunc('R'), 2, 8, false );
}

void onMouseFunc(int event, int x, int y, int , void *user_data)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        Point2f *params = (Point2f*)user_data;
        params->x  = x;
        params->y  = y;
        //cout << x << "/" << y << endl;
    }
}

void imgRotateFunc(Mat &src, Mat &dst, double angle)
{
    int length = max(src.cols, src.rows);
    Point2f pt(length/2., length/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);

    warpAffine(src, dst, r, Size(length, length));
}

void getPtsLocFunc(Mat &img, vector<Point2f> &pts, const string name )
{
    imshow( name, img );                   // Show image.
    for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Get points=====
        setMouseCallback( name, onMouseFunc, (void*) &*it );   // solve "iterator can not be converted to void*"
        waitKey(0);
        drawCircleFunc( img, *it, 'B' );
        imshow( name, img );
    }
    if(pts.size() == 4)   {
        for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Draw lines=====
            auto next = it+1 != pts.end() ? it+1 : pts.begin();
            drawLineFunc( img, *it , *next, 'G');
            imshow( name, img );
        }
    }
    else   {
        for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Draw lines=====
            auto next = it+1;
            if( (it-pts.begin())%2 == 0)
                {   drawLineFunc( img, *it , *next, 'G');   }
            imshow( name, img );
        }
    }
}
