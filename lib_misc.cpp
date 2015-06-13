#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lib_misc.h"
#include "lib_math.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

//------------------------------------------------------------------------
Scalar colorVect(const char color_name)
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



void drawCircle( Mat &img, Point center, char color )
{
    int thickness = 2;
    int lineType = 8;
    circle(img, center, 5, colorVect(color), thickness, lineType );
}

void drawLine( Mat &img, Point2f pt1, Point2f pt2, char color )
{
    int thickness = 2;
    int lineType = 8;
    int lineShift = 0;

    line(img, pt1, pt2, colorVect(color), thickness, lineType, lineShift );
}

void onMouse(int event, int x, int y, int , void *user_data)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        Point2f *params = (Point2f*)user_data;
        params->x  = x;
        params->y  = y;
        //cout << x << "/" << y << endl;
    }
}

void imgRotate(Mat &src, Mat &dst, double angle)
{
    int length = max(src.cols, src.rows);
    Point2f pt(length/2., length/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);

    warpAffine(src, dst, r, Size(length, length));
}

void getPtsLoc(Mat &img, vector<Point2f> &pts, const string name )
{
    imshow( name, img );                   // Show image.
    for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Get points=====
        setMouseCallback( name, onMouse, (void*) &*it );   // solve "iterator can not be converted to void*"
        waitKey(0);
        drawCircle( img, *it, 'B' );
        imshow( name, img );
        // //cout << "pts" << *it << endl;
    }
    if(pts.size() == 4)   {
        for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Draw lines=====
            auto next = it+1 != pts.end() ? it+1 : pts.begin();
            drawLine( img, *it , *next, 'G');
            imshow( name, img );
        }
    }
    else   {
        for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Draw lines=====
            auto next = it+1;
            if( (it-pts.begin())%2 == 0)
                {   drawLine( img, *it , *next, 'G');   }
            imshow( name, img );
        }
    }
}
