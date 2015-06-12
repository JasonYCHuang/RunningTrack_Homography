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
#include "system.h"
#include "scale_estimation.h"

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

// You can use this function to set your camera configuration.
void writeYAMLConfig()
{
    string filename = "camera_config.yaml";
    FileStorage fs(filename, FileStorage::WRITE);

    // configurations for SportTrack
    fs << "SportTrack";
    fs << "{" <<    "focus_u" << 1000.0;
    fs <<           "focus_v" << 1000.0;
    fs <<           "center_u" << 831.0;
    fs <<           "center_v" << 388.0 << "}";

    // configurations for HomeTrack
    fs << "HomeTrack";
    fs << "{" <<    "focus_u" << 801.08310;
    fs <<           "focus_v" << 805.38312;
    fs <<           "center_u" << 442.21533;
    fs <<           "center_v" << 284.83506 << "}";

    fs.release();
}

void readYAMLConfig(System::calibration &params)
{
    // Select the track type. // If you don't have multiple track types, you can hide/comment this part.
    string select_track, track_name = "SportTrack";
    while( !(select_track=="1" || select_track=="2") ) {
        cout << "[1]SportTrack? or [2]HomeTrack? input 1 or 2: ";
        cin >> select_track;
    }
    if (select_track=="2")   {
        track_name = "HomeTrack";
    }

    // Read the YAML file to get system configurations.
    string filename = "camera_config.yaml";
    FileStorage fs(filename, FileStorage::READ);
    fs.open(filename, FileStorage::READ);
    FileNode node = fs[track_name];
    // Set parameters
    params.fu = (double) node["focus_u"];
    params.fv = (double) node["focus_v"];
    params.center = Point2f( (double) node["center_u"],  (double) node["center_v"] );
    params.resetCameraInternalMatrix();
    // release the YAML file.
    fs.release();
}

string setImageName()
{
    string name;
    cout << "Input the name of the original image: ";
    cin >> name;
    return name;
}

// Start the main funtion.
int main()
{
    //writeYAMLConfig();      // Uncomment this line if you want to set your own camera configuration.

    // Set camera internal parameters from YAML.
    System::calibration params_yaml;
    readYAMLConfig(params_yaml);

    // Set the original image
    string img_name_ori = setImageName();                       // Input the image name.
    Mat img_ori = imread(img_name_ori, CV_LOAD_IMAGE_COLOR);    // Read the file.
    Mat img_process = img_ori.clone();
    while(!img_ori.data && !img_process.data)    {                                   // Check for invalid input.
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl << endl ;
        img_name_ori = setImageName();
        img_ori = imread(img_name_ori, CV_LOAD_IMAGE_COLOR);
        img_process = img_ori.clone();
    }

    // Initialized the "SacleEstimation" object.
    SacleEstimation myApp(params_yaml);

    // Status
    cout << "Processing: Frame: " << "i" << "-------------------------------------" << endl;

    // Start to process the image.
    if (myApp.process(img_process)) {
        cout << " ... Success!" << endl;
    }   else    {
        cout << " ... failed!" << endl;
    }

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
