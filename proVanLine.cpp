#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lib_misc.h"
#include "lib_math.h"
#include "proVanLine.h"
#include "theline.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;
//-------------------------------------------------------
vector<double> differentialFunc(const vector<double> in)
{
    vector<double> out(in.size()-1);
    for(unsigned int i=0; i<in.size()-1; ++i)   {
        out[i] = in[i] - in[i+1];
        cout << out[i] << endl;//
    }
    return out;
}

void calcVanLineFunc(const vector<Point2f> &pts, Mat &img)
{
    vector<TheLine> pL(pts.size()/2);
    for (unsigned int i=0; i<pL.size(); ++i)    {
        pL[i].setLineParam(pts[i*2], pts[i*2+1]);
    }

    Mat vanishingLinevector;
    //MVG page218, 8-15
    auto L0XL1 = pL[0].vect().cross(pL[1].vect());
    auto L0XL2 = pL[0].vect().cross(pL[2].vect());
    auto L1XL2 = pL[1].vect().cross(pL[2].vect());
    auto L2XL1 = pL[2].vect().cross(pL[1].vect());
    double block1 = L0XL2.dot(L1XL2);
    double block2 = L0XL1.dot(L2XL1);

    vanishingLinevector = block1*(pL[1].vect()) + 2*block2*(pL[2].vect());
    double deg = atan(-vanishingLinevector.at<double>(0,0)/vanishingLinevector.at<double>(1,0))*TO_DEG;

    Point2f one, two;
    one.x = 200;
    two.x = 600;
    one.y = ( -vanishingLinevector.at<double>(2,0) - vanishingLinevector.at<double>(0,0)*one.x ) / vanishingLinevector.at<double>(1,0) + 500;
    two.y = ( -vanishingLinevector.at<double>(2,0) - vanishingLinevector.at<double>(0,0)*two.x ) / vanishingLinevector.at<double>(1,0) + 500;

    drawLineFunc( img, one, two, 'R' );
    imshow( "L", img );

    cout << -vanishingLinevector.at<double>(0,0)/vanishingLinevector.at<double>(1,0) << endl;
    cout << deg << endl << endl;
    cout << one  << endl;
    cout << two  << endl;
}





void getVanLineFunc(const string name)
{
    Mat img;
    img = imread(name, CV_LOAD_IMAGE_COLOR);   // Read the file
    if( !img.data)   {         // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {
        //=====Calc vanishing point=====
        vector<Point2f> selected_pts(6);
        getPtsLocFunc(img, selected_pts, name);
        vector<Point2f> selected_pts_for_vp{selected_pts[0], selected_pts[1], selected_pts[2], selected_pts[3]};
        Point2f vanish_pts = calcVanPtsFunc(img, selected_pts_for_vp, name);
        //======Calc vanishing line=====
        calcVanLineFunc(selected_pts, img);

        waitKey(0);
        destroyAllWindows();
    }
}




void projectVanLine()
{
    string name_ori;
    cout << "=> Input the name of the original image." << endl;
    cin >> name_ori;
    getVanLineFunc(name_ori);
    cout << endl << endl << endl;
}
