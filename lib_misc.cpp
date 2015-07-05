#include "lib_misc.h"

using namespace cv;
using namespace std;

//------------------------------------------------------------------------
Scalar colorScalar(const char color_name)
{
    Scalar colorScalar = Scalar( 0, 0, 0 );
    switch (color_name)   {
        case 'R' :
            colorScalar = Scalar( 0, 0, 255 );
            break;
        case 'G' :
            colorScalar = Scalar( 0, 255, 0 );
            break;
        case 'B' :
            colorScalar = Scalar( 255, 0, 0 );
            break;
        case 'M' :
            colorScalar = Scalar( 255, 0, 255 );
            break;
        case 'Y' :
            colorScalar = Scalar( 0, 255, 255 );
            break;
        case 'K' :
            colorScalar = Scalar( 0, 0, 0 );
            break;
    }
    return colorScalar;
}

void onMouse(int event, int x, int y, int , void *user_data)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        Point2f *params = (Point2f*)user_data;
        params->x  = x;
        params->y  = y;
        //cout << x << "/" << y << endl;
    }
}

void imgRotate(Mat &src, Mat &dst, double angle)
{
    int length = max(src.cols, src.rows);
    Point2f pt(length/2., length/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);

    warpAffine(src, dst, r, Size(length, length));
}

void getPtsLoc(Mat &img, vector<Point2f> &pts, const string name )
{

    // the1
    pts.clear();
    pts.push_back(Point2f(956, 635));
    pts.push_back(Point2f(926, 490));
    pts.push_back(Point2f(985, 497));
    pts.push_back(Point2f(1119, 636));
    pts.push_back(Point2f(1280, 629));
    pts.push_back(Point2f(960, 450));


 /*
    // the2
    pts.clear();
    pts.push_back(Point2f(938, 771));
    pts.push_back(Point2f(911, 535));
    pts.push_back(Point2f(934, 523));
    pts.push_back(Point2f(1132, 771));
    pts.push_back(Point2f(1108, 629));
    pts.push_back(Point2f(1313, 772));
*/
    /*
    // the3
    pts.clear();
    pts.push_back(Point2f(855, 772));
    pts.push_back(Point2f(805, 490));
    pts.push_back(Point2f(835, 493));
    pts.push_back(Point2f(1083, 772));
    pts.push_back(Point2f(843, 480));
    pts.push_back(Point2f(1325, 772));
 */
    for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Get points=====
        //setMouseCallback( name, onMouse, (void*) &*it );   // solve "iterator can not be converted to void*"
        //waitKey(0);
        circle(img, *it, 5, colorScalar('B'), 2, 8, 0);
        imshow( name, img );
    }
    waitKey(0);



    /*
    imshow( name, img );                   // Show image.
    for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Get points=====
        setMouseCallback( name, onMouse, (void*) &*it );   // solve "iterator can not be converted to void*"
        waitKey(0);
        circle(img, *it, 5, colorScalar('B'), 2, 8, 0);
        imshow( name, img );
        // //cout << "pts" << *it << endl;
    }
    if(pts.size() == 4)   {
        for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Draw lines=====
            auto next = it+1 != pts.end() ? it+1 : pts.begin();
            line(img, *it, *next, colorScalar('G'), 1, 8, 0);
            imshow( name, img );
        }
    }
    else   {
        for(auto it = pts.begin(); it != pts.end(); ++it)   {   //=====Draw lines=====
            auto next = it+1;
            if( (it-pts.begin())%2 == 0)
                {   line(img, *it, *next, colorScalar('G'), 1, 8, 0);   }
            imshow( name, img );
        }
    }
    */
}
