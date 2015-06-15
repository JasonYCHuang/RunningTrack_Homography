#include <iostream>
#include <sstream>
#include <stdio.h>

#include "lib_misc.h"
#include "lib_math.h"
#include "system.h"
#include "scale_estimation.h"

using namespace cv;
using namespace std;

// You can use this function to set your camera configuration.
void writeYAMLConfig()
{
    string file_name = "sport_track_config.yaml";
    FileStorage fs(file_name, FileStorage::WRITE);

    /*
    // configurations for SportTrack
    fs << "SportTrack";
    fs << "{" <<    "focus_u" << 1000.0;
    fs <<           "focus_v" << 1000.0;
    fs <<           "center_u" << 831.0;
    fs <<           "center_v" << 388.0 << "}";

    // configurations for SportTrack
    fs << "SportTrack";
    fs << "{" <<    "focus_u" << 682.504;
    fs <<           "focus_v" << 682.504;
    fs <<           "center_u" << 747.0;
    fs <<           "center_v" << 350.0 << "}";
    */
    // configurations for SportTrack
    fs << "SportTrack";
    fs << "{" <<    "focus_u" << 682.504;
    fs <<           "focus_v" << 682.504;
    fs <<           "center_u" << 747.0;
    fs <<           "center_v" << 350.0 << "}";

    // configurations for HomeTrack
    fs << "HomeTrack";
    fs << "{" <<    "focus_u" << 801.08310;
    fs <<           "focus_v" << 805.38312;
    fs <<           "center_u" << 442.21533;
    fs <<           "center_v" << 284.83506 << "}";

    // Settings for processing the bird view.
    fs << "num_lines_for_vline"  << 3;
    fs << "num_lines_for_vpoint" << 2;

    fs.release();
}

void readYAMLConfig(System::calibration &params_1, System::setting &params_2)
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
    string file_name = "sport_track_config.yaml";
    FileStorage fs(file_name, FileStorage::READ);
    fs.open(file_name, FileStorage::READ);
    FileNode node = fs[track_name];
    // Set calibration parameters
    params_1.fu = (double) node["focus_u"];
    params_1.fv = (double) node["focus_v"];
    params_1.center = Point2f( (double) node["center_u"],  (double) node["center_v"] );
    params_1.resetCameraInternalMatrix();
    // Set bird_view parameters
    params_2.num_lines_for_vline = (int) fs["num_lines_for_vline"];
    params_2.num_lines_for_vpoint = (int) fs["num_lines_for_vpoint"];

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

void proBirdView()
{
    //writeYAMLConfig();      // Uncomment this line if you want to set your own camera configuration.

    // Set camera internal parameters from YAML.
    System::calibration params_c;
    System::setting params_s;
    readYAMLConfig(params_c, params_s);

    // Set the original image
    string img_name_ori = setImageName();                       // Input the image name.
    Mat img_ori = imread(img_name_ori, CV_LOAD_IMAGE_COLOR);    // Read the file.
    Mat img_process = img_ori.clone();
    while(!img_ori.data || !img_process.data)    {              // Check for invalid input.
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl << endl ;
        img_name_ori = setImageName();
        img_ori = imread(img_name_ori, CV_LOAD_IMAGE_COLOR);
        img_process = img_ori.clone();
    }

    // Initialized the "SacleEstimation" object.
    SacleEstimation myApp(params_c, params_s);

    // Status   TBD
    cout << "Processing: Frame: " << "i" << "-------------------------------------" << endl;

    // Start to process the image.
    if (myApp.process(img_process)) {
        cout << " ... Success!" << endl;
    }   else    {
        cout << " ... failed!" << endl;
    }

}


// Start the main funtion.
int main()
{
    proBirdView();

    return 0;
}
