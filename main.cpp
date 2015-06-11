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



// Welcome message for users to select functions.
char userSelect(bool &ci)
{
    if (ci)     {   // Normal condition.
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
    else    {       // The user didn't type a valid input.
        cout << endl << endl << "--- Invalid input! ---" << endl;
        ci = true;
    }
    char is;
    cin >> is;

    return is;
}

// Start the main funtion.
int main()
{


    /*
    char program_select = '0';
    bool brk_token = false, valid_input = true;
    while(!brk_token)    {
        program_select = userSelect(valid_input);
        switch (program_select) {
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
                brk_token = true;   // terminate the program.
                break;
            default:
                valid_input = false;
                break;
        }
    }
    */

    return 0;
}
