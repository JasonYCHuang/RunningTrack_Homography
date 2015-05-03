#include <iostream>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#include "lib_misc.h"
#include "lib_math.h"
#include "proHgByFeatures.h"

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;
//-------------------------------------------------------

void hgTransByFeaturesFunc(const string name_ori, const string name_ref)
{
    Mat img_ori, img_ref;
    img_ori = imread(name_ori, CV_LOAD_IMAGE_COLOR);   // Read the 1st file
    img_ref = imread(name_ref, CV_LOAD_IMAGE_COLOR);   // Read the 2nd file
    if( !img_ori.data || !img_ref.data)   {         // Check for invalid input
        cout <<  " <Incorrect Usage> Could not open or find the image" << endl ;
    }
    else    {
        //=====Display 1st image=====
        Mat img_1 = img_ori.clone();          // img_painted & img_original are independent.
        //namedWindow( name_ori, WINDOW_AUTOSIZE );      // Create a window for display.
        //=====Display 2nd image=====
        Mat img_2 = img_ref.clone();          // img_painted & img_original are independent.
        //namedWindow( name_ref, WINDOW_AUTOSIZE );      // Create a window for display.



          int minHessian = 400;
          std::vector<KeyPoint> keypoints_1, keypoints_2;

          SurfFeatureDetector detector( minHessian );
          detector.detect( img_1, keypoints_1 );
          detector.detect( img_2, keypoints_2 );

          cout << "minHessian = " << minHessian << endl;
          cout << "#kp = " << keypoints_1.size() << endl;

          //-- Step 2: Calculate descriptors (feature vectors)
          SurfDescriptorExtractor extractor;
          Mat descriptors_1, descriptors_2;
          extractor.compute( img_1, keypoints_1, descriptors_1 );
          extractor.compute( img_2, keypoints_2, descriptors_2 );
          //-- Step 3: Matching descriptor vectors using FLANN matcher
          FlannBasedMatcher matcher;
          std::vector< DMatch > matches;
          matcher.match( descriptors_1, descriptors_2, matches );

          double max_dist = 0; double min_dist = 10;

          //-- Quick calculation of max and min distances between keypoints
          for( int i = 0; i < descriptors_1.rows; i++ )
          { double dist = matches[i].distance;
            if( dist < min_dist ) min_dist = dist;
            if( dist > max_dist ) max_dist = dist;
          }

          printf("-- Max dist : %f \n", max_dist );
          printf("-- Min dist : %f \n", min_dist );

          //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
          //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
          //-- small)
          //-- PS.- radiusMatch can also be used here.
          std::vector< DMatch > good_matches;
          bool token = true;
          double criteria_dist = 2*min_dist;
          while(token)   {
              std::vector< DMatch > temp_matches;
              for( int i = 0; i < descriptors_1.rows; i++ )
              { if( matches[i].distance <= criteria_dist )
                { temp_matches.push_back( matches[i]); }
              }
              if(temp_matches.size()<=6 || temp_matches.size() == 0)    {
                  token = false;
                  good_matches = temp_matches;
              }
              criteria_dist*=0.9;
          }


          //-- Draw only "good" matches
          Mat img_matches;
          drawMatches( img_1, keypoints_1, img_2, keypoints_2,
                       good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                       vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

          //-- Show detected matches
          namedWindow( "Good Matches", WINDOW_AUTOSIZE );
          imshow( "Good Matches", img_matches );

          for( int i = 0; i < (int)good_matches.size(); i++ )
          { printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  -- dist: %f \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx, good_matches[i].distance ); }








        /*

        //-- Step 1: Detect the keypoints using SURF Detector
        int minHessian = 10000;
        std::vector<KeyPoint> keypoints_object, keypoints_scene;
        for(minHessian; keypoints_object.size()<10; minHessian*=0.8)    {
            SurfFeatureDetector detector( minHessian );
            detector.detect( img_object, keypoints_object );
            detector.detect( img_scene, keypoints_scene );
        }

        cout << "minHessian = " << minHessian << endl;


        //-- Step 2: Calculate descriptors (feature vectors)
        SurfDescriptorExtractor extractor;

        Mat descriptors_object, descriptors_scene;

        extractor.compute( img_object, keypoints_object, descriptors_object );
        extractor.compute( img_scene, keypoints_scene, descriptors_scene );

        //-- Step 3: Matching descriptor vectors using FLANN matcher
        FlannBasedMatcher matcher;
        std::vector< DMatch > matches;
        matcher.match( descriptors_object, descriptors_scene, matches );

        double max_dist = 0; double min_dist = 100;

        //-- Quick calculation of max and min distances between keypoints
        for( int i = 0; i < descriptors_object.rows; i++ )
        {
            double dist = matches[i].distance;
            if( dist < min_dist ) min_dist = dist;
            if( dist > max_dist ) max_dist = dist;
        }

        printf("-- Max dist : %f \n", max_dist );
        printf("-- Min dist : %f \n", min_dist );

        //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
        std::vector< DMatch > good_matches;

        for( int i = 0; i < descriptors_object.rows; i++ )
        { if( matches[i].distance < 3*min_dist )
             { good_matches.push_back( matches[i]); }
        }

        Mat img_matches;
        drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
                       good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                       vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

        //-- Localize the object
        std::vector<Point2f> obj;
        std::vector<Point2f> scene;

        for( int i = 0; i < good_matches.size(); i++ )
        {
            //-- Get the keypoints from the good matches
            obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
            scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
        }

        Mat H = findHomography( obj, scene, CV_RANSAC );

        //-- Get the corners from the image_1 ( the object to be "detected" )
        std::vector<Point2f> obj_corners(4);
        obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
        obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
        std::vector<Point2f> scene_corners(4);

        perspectiveTransform( obj_corners, scene_corners, H);

        //-- Draw lines between the corners (the mapped object in the scene - image_2 )
        line( img_matches, scene_corners[0] + Point2f( img_object.cols, 0), scene_corners[1] + Point2f( img_object.cols, 0), Scalar(0, 255, 0), 4 );
        line( img_matches, scene_corners[1] + Point2f( img_object.cols, 0), scene_corners[2] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
        line( img_matches, scene_corners[2] + Point2f( img_object.cols, 0), scene_corners[3] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
        line( img_matches, scene_corners[3] + Point2f( img_object.cols, 0), scene_corners[0] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );

        //-- Show detected matches
        imshow( "Good Matches & Object detection", img_matches );

        */

        imwrite( "./HgByFeature.jpg", img_matches );
        waitKey(0);

        destroyAllWindows();
    }
}

void projectHgByFeatures()
{
    string name_ori, name_ref;
    cout << "=> Input the name of the original image." << endl;
    cin >> name_ori;
    cout << "=> Input the name of the reference image." << endl;
    cin >> name_ref;
    hgTransByFeaturesFunc(name_ori, name_ref);
    cout << endl << endl << endl;
}
