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
vector<double> differentialFunc(const vector<double> in)
{
    vector<double> out(in.size()-1);
    for(int i=0; i<in.size()-1; ++i)   {
        out[i] = in[i] - in[i+1];
        cout << out[i] << endl;//
    }
    return out;
}

void calcVanLineFunc(const vector<Point2f> &pts)
{
    int pair = pts.size()/2;
    vector<double> deg(pair);    //2 points can form a line.
    for(int i=0; i<pair; ++i)   {
        double slp = slopeFunc(pts[i*2], pts[i*2+1]);
        deg[i] = atan(slp)*TO_DEG;
        if(deg[i] < 0)
        {   deg[i] = deg[i] + 180;  }
        cout << deg[i] << endl;
    }

    vector<double>  diff_deg = differentialFunc(deg);
    cout << endl;//
    vector<double>  diff2_deg = differentialFunc(diff_deg);
    double ratio, deg_sum, roll;
    if(*diff_deg.begin() < *(diff_deg.end()-1)) {
        ratio = *diff_deg.begin() / *(diff_deg.begin()+1);
        deg_sum = *diff_deg.begin() / (1-ratio);  //ration must smaller than 1
        roll = *(deg.begin()+1) + deg_sum;
    }
    else    {
        ratio = *(diff_deg.end()-1) / *(diff_deg.end()-2);
        deg_sum = *(diff_deg.end()-1) / (1-ratio);  //ration must smaller than 1
        roll = *(deg.end()-2) - deg_sum;
    }
    cout << "roll = " << roll << endl;
    cout << "deg_sum = " << deg_sum << endl;
    cout << "ratio = " << ratio << endl;
    cout << *(deg.begin()+1) << endl <<  *(deg.end()-2) << endl;















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

