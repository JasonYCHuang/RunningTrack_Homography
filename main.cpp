#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;



Scalar ColorVectFunc(char color_name)
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



void DrawCircleFunc( Mat img, Point center, char color )
{
    int thickness = 2;
    int lineType = 8;
    circle(img, center, 5, ColorVectFunc(color), thickness, lineType );
}

void DrawLineFunc( Mat img, Point2f pt1, Point2f pt2, char color )
{
    int thickness = 2;
    int lineType = 8;
    int lineShift = 0;

    line(img, pt1, pt2, ColorVectFunc(color), thickness, lineType, lineShift );
}

void onMouseFunc(int event, int x, int y, int flags, void* user_data)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        Point2f *params = (Point2f*)user_data;
        params->x  = x;
        params->y  = y;
    }
}

void imgRotateFunc(Mat &src, Mat &dst, double angle)
{
    int length = max(src.cols, src.rows);
    Point2f pt(length/2., length/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);

    warpAffine(src, dst, r, Size(length, length));
}




int main(int argc, char* argv[])
{

    //=====Loading image=====
    if( argc != 2)
    {
        cout <<" <Incorrect Usage> you should input : ./Homography2D your_image.jpg" << endl;
        return -1;
    }

    Mat img_original;
    img_original = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! img_original.data )                              // Check for invalid input
    {
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
        return -1;
    }


    //=====Display image=====
    string name_img = "Display the image";
    Mat img_painted = img_original.clone();          // img_painted & img_original are independent.
    namedWindow( name_img, CV_WINDOW_KEEPRATIO );      // Create a window for display.
    imshow( name_img, img_original );                   // Show our image inside it.

    //=====Get points by mouse clicking=====
    Point2f selected_pts[4];
    int i;

    for(i = 0; i<4; i++)
    {
        setMouseCallback( name_img, onMouseFunc, (void*)&selected_pts[i]);
        waitKey(0);

        DrawCircleFunc( img_painted, selected_pts[i], 'B' );
        imshow( name_img, img_painted );
    }
    //=====Draw lines=====
    for(i = 0; i<4; i++)
    {
        int end_pt_num = i==3 ? 0 : i+1;
        DrawLineFunc( img_painted, selected_pts[i] , selected_pts[end_pt_num], 'G');
        imshow( name_img, img_painted );
    }

    waitKey(0);                                          // Wait for a keystroke in the window

    //======Define Target points=======
    Point2f ideal_pts[4];
    ideal_pts[0] =  Point2f(0, 0);
    ideal_pts[1] =  Point2f(80, 0);
    ideal_pts[2] =  Point2f(80, 50);
    ideal_pts[3] =  Point2f(0, 50);

    //======Calc transformation_matrix=======
    //Mat transformation_matrix;
    //transformation_matrix = getPerspectiveTransform(selected_pts, ideal_pts);
    //cout << "transformation_matrix" << endl << transformation_matrix << endl;

    Mat mapping_matrix = (Mat_<double>(8,8) << selected_pts[0].x, selected_pts[0].y ,1, 0, 0, 0, -1*selected_pts[0].x*ideal_pts[0].x, -1*selected_pts[0].y*ideal_pts[0].x,
                                               0, 0, 0, selected_pts[0].x, selected_pts[0].y ,1, -1*selected_pts[0].x*ideal_pts[0].y, -1*selected_pts[0].y*ideal_pts[0].y,
                                               selected_pts[1].x, selected_pts[1].y ,1, 0, 0, 0, -1*selected_pts[1].x*ideal_pts[1].x, -1*selected_pts[1].y*ideal_pts[1].x,
                                               0, 0, 0, selected_pts[1].x, selected_pts[1].y ,1, -1*selected_pts[1].x*ideal_pts[1].y, -1*selected_pts[1].y*ideal_pts[1].y,
                                               selected_pts[2].x, selected_pts[2].y ,1, 0, 0, 0, -1*selected_pts[2].x*ideal_pts[2].x, -1*selected_pts[2].y*ideal_pts[2].x,
                                               0, 0, 0, selected_pts[2].x, selected_pts[2].y ,1, -1*selected_pts[2].x*ideal_pts[2].y, -1*selected_pts[2].y*ideal_pts[2].y,
                                               selected_pts[3].x, selected_pts[3].y ,1, 0, 0, 0, -1*selected_pts[3].x*ideal_pts[3].x, -1*selected_pts[3].y*ideal_pts[3].x,
                                               0, 0, 0, selected_pts[3].x, selected_pts[3].y ,1, -1*selected_pts[3].x*ideal_pts[3].y, -1*selected_pts[3].y*ideal_pts[3].y  );
    Mat inv_mapping_matrix, transformation_params;
    Mat ideal_pt_matrix = (Mat_<double>(8,1) << ideal_pts[0].x, ideal_pts[0].y, ideal_pts[1].x, ideal_pts[1].y, ideal_pts[2].x, ideal_pts[2].y, ideal_pts[3].x, ideal_pts[3].y);
    invert(mapping_matrix, inv_mapping_matrix);
    transformation_params = inv_mapping_matrix*ideal_pt_matrix;
    Mat transformation_matrix = (Mat_<double>(3,3) << transformation_params.at<double>(0,0), transformation_params.at<double>(1,0), transformation_params.at<double>(2,0),
                                                       transformation_params.at<double>(3,0), transformation_params.at<double>(4,0), transformation_params.at<double>(5,0),
                                                       transformation_params.at<double>(6,0), transformation_params.at<double>(7,0), 1 );

    //======Draw Bird view image and rotate it=======
    Mat img_transformed;
    warpPerspective(img_painted, img_transformed, transformation_matrix, img_painted.size());

    Mat img_trans_rotated;
    imgRotateFunc(img_transformed, img_trans_rotated, 90);

    string name_img_trans_rotated = "Bird view image";
    namedWindow( name_img_trans_rotated, CV_WINDOW_KEEPRATIO );
    imshow( name_img_trans_rotated, img_trans_rotated );

    waitKey(0);

    imwrite( "./OriginalImg.jpg", img_painted );
    imwrite( "./BirdViewImg.jpg", img_trans_rotated );

    return 0;
}
