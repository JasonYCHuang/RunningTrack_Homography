#ifndef FUNC2_H
#define FUNC2_H

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
    //-------------------------------------------------------

    Scalar colorVectFunc(char color_name);
    void drawCircleFunc( Mat img, Point center, char color );
    void drawLineFunc( Mat img, Point2f pt1, Point2f pt2, char color );
    void onMouseFunc(int event, int x, int y, int , void* user_data);
    void imgRotateFunc(Mat &src, Mat &dst, double angle);
    void get4RandPts(Mat &img, vector<Point2f> &pts, const string name );
    void hgTransformFunc(Mat &ori, Mat &ref, Mat &target, Mat &h_matrix, const string n1, const string n2);
    void hgTransBy4RandPtsFunc(const string name_ori, const string name_ref);
    void projectHgTra4Pts();

#endif // FUNC2_H
