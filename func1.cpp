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
//-------------------------------------------------------

void optionsFunc(char &is, bool &ci)
{
    if (ci)     {
        cout << endl << endl << endl;
        cout << "-----Please select the program you want to execute!-----" << endl;
        cout << "[1] Homography transformation from 4-random-points of 2 images." << endl;
        cout << "[2] Homography transformation from 4-vertex to fit into a rectangle." << endl;
        cout << "[3] Homography transformation of lines." << endl;
        cout << "[4] Rotation matrix from vanishing points." << endl;
        cout << "-----Input a number or '0' to terminate the program-----" << endl;
    }
    else    {
        ci = true;
    }
    cin >> is;
}

void selectProgFunc()
{
    char progNum = '0';
    bool brkToken = false, corrInput = true;

    while(!brkToken)    {
        optionsFunc(progNum, corrInput);
        switch (progNum) {
            case '1':
                projectHgTra4Pts();
                break;
            case '2':
                cout << "2*" << endl; //TBD
                break;
            case '3':
                cout << "3*" << endl;  //TBD
                break;
            case '4':
                projectRotByVanPts();
                break;
            case '0':
                cout << "See You Next Time!!" << endl;
                brkToken = true;   // terminate the program.
                break;
            default:
                cout << endl << endl;
                cout << "Invalid input!! Input must be a number! (input '0' to terminate the program)" << endl;
                corrInput = false;
                break;
        }
    }
}
