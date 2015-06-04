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

Mat calcVanLineSVDFunc(const vector<Point2f> &pts, Mat &img)
{
    //Set Mat for SVD: A=U*D*VT
    Mat A, U, D, VT, V;

    //Convert points to lines, and create A matrix by DLT.
    vector<TheLine> line(pts.size()/2);
    for (unsigned int i=0; i<line.size(); ++i)    {
        line[i].setLineParam(pts[i*2], pts[i*2+1], (1+i));
        Mat temp1 = (Mat_<double>(1,6) << 0, 0, -line[i].lamb(), -1, line[i].lamb()*line[i].b(), line[i].b());
        Mat temp2 = (Mat_<double>(1,6) << line[i].lamb(), 1, 0, 0, -line[i].lamb()*line[i].a(), -line[i].a());
        A.push_back(temp1);
        A.push_back(temp2);
    }

    //Solve SVD. vLine is equal to the 1st row of A.
    SVD::compute(A, D, U, VT);
    V = VT.t();
    Mat vLine = (Mat_<double>(3,1) << V.at<double>(0,5), V.at<double>(2,5), V.at<double>(4,5) );

    //Determine 2 points for vLine, and draw the vanishing line base on them.
    Point2f one, two;
    one.x = 200;
    two.x = 600;
    one.y = -( vLine.at<double>(2,0) + vLine.at<double>(0,0)*one.x ) / vLine.at<double>(1,0) ;
    two.y = -( vLine.at<double>(2,0) + vLine.at<double>(0,0)*two.x ) / vLine.at<double>(1,0) ;
    //Make a shift to ensure the vanishing line is in the field of view.
    double shift;
    if(one.y<0 || two.y<0)  {
        shift = (one.y < two.y) ? -one.y : -two.y;
    }
    one.y += shift;
    two.y += shift;
    //Draw the vanishing line
    drawLineFunc( img, one, two, 'R' );
    imshow( "vLine", img );
    imwrite( "./vLineA.jpg", img );

    //Normalize vLine, that is make the 3rd element to 1.
    Mat vLineNormalized = (Mat_<double>(3,1) << V.at<double>(0,5)/V.at<double>(4,5), V.at<double>(2,5)/V.at<double>(4,5), 1 );

    return vLineNormalized;
}




void getVanLineFunc(const string name)
{
    Mat img;
    img = imread(name, CV_LOAD_IMAGE_COLOR);   // Read the file
    if( !img.data)   {         // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {                  //if img data is valid, process it!
        //Fetch feature points
        vector<Point2f> selected_pts(8);
        getPtsLocFunc(img, selected_pts, name);
        vector<Point2f> selected_pts_for_vp{selected_pts[0], selected_pts[1], selected_pts[2], selected_pts[3]};

        //Calculate vanishing point
        Mat vanishingPoint = calcVanPtsFunc(img, selected_pts_for_vp, name);

        //Calculate vanishing line
        Mat vanishingLine = calcVanLineSVDFunc(selected_pts, img);

        //Calculate surface normal
        Mat N = (K.t())*(vanishingLine);
        N = N/norm(N);
        cout << "normal" << N << endl << endl;

        //Calculate rotaion matrix
        Mat R1, R2, R3;
        R1 = (K.inv()) * vanishingPoint / norm( (K.inv())*vanishingPoint );
        R3 = (K.t()) * vanishingLine / norm( (K.t())*vanishingLine );
        R2 = R1.cross(R3);
        cout << "R1" << R1 << endl;
        cout << "R2" << R2 << endl;
        cout << "R3" << R3 << endl;
    }
    waitKey(0);
    destroyAllWindows();
}




void projectVanLine()
{
    string name_ori;
    cout << "=> Input the name of the original image." << endl;
    cin >> name_ori;
    getVanLineFunc(name_ori);
    cout << endl << endl << endl;
}

















/*
 *


void calcVanLineMVGFunc(const vector<Point2f> &pts, Mat &img)
{
    vector<TheLine> pL(pts.size()/2);
    for (unsigned int i=0; i<pL.size(); ++i)    {
        pL[i].setLineParam(pts[i*2], pts[i*2+1], (1+i));
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
    cout << "vanishingLinevector " << vanishingLinevector << endl;

    Point2f one, two;
    one.x = 100;
    two.x = 500;
    one.y = -( vanishingLinevector.at<double>(2,0) + vanishingLinevector.at<double>(0,0)*one.x ) / vanishingLinevector.at<double>(1,0) ;
    two.y = -( vanishingLinevector.at<double>(2,0) + vanishingLinevector.at<double>(0,0)*two.x ) / vanishingLinevector.at<double>(1,0) ;

    drawLineFunc( img, one, two, 'R' );
    imshow( "L", img );
    imwrite( "./vLine_L0.jpg", img );

    double deg = atan(-vanishingLinevector.at<double>(0,0)/vanishingLinevector.at<double>(1,0))*TO_DEG;
    cout << "deg" << deg << endl << endl;
    cout << one  << endl;
    cout << two  << endl;
}

*/
