#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lib_misc.h"
#include "lib_math.h"
#include "vanLine.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;
//-------------------------------------------------------


void calcVanLineFunc(const vector<Point2f> &pts)
{
    int pair = pts.size()/2;
    vector<double> deg(pair), diff_deg(pair-1);    //2 points can form a line.
    for(int i=0; i<pair; ++i)   {
        double slp = slopeFunc(pts[i*2], pts[i*2+1]);
        deg[i] = atan(slp)*TO_DEG;
        if(deg[i] < 0)
        {   deg[i] = deg[i] + 180;  }
    }
    for(int i=0; i<pair-1; ++i)   {
        diff_deg[i] = deg[i] - deg[i+1];
        cout << deg[i] << " | " << deg[i+1] << " | " << diff_deg[i] << endl;
    }





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
        vector<Point2f> selected_pts(8);
        getPtsLocFunc(img, selected_pts, name);
        vector<Point2f> selected_pts_for_vp{selected_pts[0], selected_pts[1], selected_pts[2], selected_pts[3]};
        Point2f vanish_pts = calcVanPtsFunc(img, selected_pts_for_vp, name);
        //======Calc vanishing line=====
        calcVanLineFunc(selected_pts);





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

