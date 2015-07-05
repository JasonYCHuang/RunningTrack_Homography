#include <iostream>
#include <sstream>
#include <stdio.h>

#include "lib_misc.h"
#include "lib_math.h"
#include "system.h"
#include "scale_estimation.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

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















    /*

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

    string window_name1 = "Original";
    namedWindow( window_name1, CV_WINDOW_AUTOSIZE );
    imshow( window_name1, img_process );
    waitKey(0);


    Mat img_detected_edges, img_detected_edges_bgr, img_blur, cdst;
    blur( img_process, img_blur, Size(3,3) );
    Canny( img_blur, img_detected_edges, 50, 200, 3);

    string window_name2 = "Canny";
    namedWindow( window_name2, CV_WINDOW_AUTOSIZE );
    imshow( window_name2, img_detected_edges );
    waitKey(0);


    string window_name3 = "Hough Transform";
    namedWindow( window_name3, CV_WINDOW_AUTOSIZE );

    vector<Vec2f> lines;
    HoughLines(img_detected_edges, lines, 1, CV_PI/180, 300, 0, 0 );
    cvtColor(img_detected_edges, img_detected_edges_bgr, CV_GRAY2BGR);

    for( size_t i = 0; i < lines.size(); i++ )
    {
      float rho = lines[i][0], theta = lines[i][1];
      Point pt1, pt2;
      double a = cos(theta), b = sin(theta);
      double x0 = a*rho, y0 = b*rho;
      pt1.y = 400;
      pt1.x = (rho-b*pt1.y)/a;
      pt2.y = 700;
      pt2.x = (rho-b*pt2.y)/a;
      line( img_detected_edges_bgr, pt1, pt2, Scalar(0,0,255), 1, CV_AA);
    }


    imshow( window_name3, img_detected_edges_bgr );
    waitKey(0);



    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat grad;

    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( img_blur, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( img_blur, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    //addWeighted( grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    Mat grad_deg;
    grad_deg = Mat::zeros(grad_x.rows, grad_x.cols, CV_16U);

    for(int i = 0; i < grad_x.rows-1; ++i) {
        for(int j = 0; j < grad_x.cols; ++j) {
            double directionRAD = atan2(grad_y.at<double>(i,j), grad_x.at<double>(i,j));
            int directionDEG = (int)(180.0 + directionRAD / M_PI * 180.0);
            grad_deg.at<int>(i,j) = directionDEG;
        }
    }


    string window_name3 = "gradient";
    imshow( window_name3, grad_deg );
    waitKey(0);
    */












    /*
    string window_name("Canny");

      /// Create a matrix of the same type and size as src (for dst)
      dst.create( img_process.size(), img_process.type() );

      /// Create a window
      namedWindow( window_name, CV_WINDOW_AUTOSIZE );

      /// Create a Trackbar for user to enter threshold
      createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

      /// Show the image
      CannyThreshold(0, 0);

      /// Wait until user exit program by pressing a key
      waitKey(0);



      void CannyThreshold(int, void*)
      {
        /// Reduce noise with a kernel 3x3
        blur( src_gray, detected_edges, Size(3,3) );

        /// Canny detector
        Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

        /// Using Canny's output as a mask, we display our result
        dst = Scalar::all(0);

        src.copyTo( dst, detected_edges);
        imshow( window_name, dst );
       }









    */



    return 0;
}
