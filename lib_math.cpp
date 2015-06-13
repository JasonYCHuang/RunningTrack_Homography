#include "lib_math.h"

using namespace cv;
using namespace std;

//-------------------------------------------------------
double calcDivision(const double numerator, const double denominator)   // Simple division, and we can use this as error handling.
{
    // TBD: divided by zero.
    return numerator/denominator;
}

Mat getRotationMatrix(double alpha, double beta, double gamma)
{
    Mat R_pitch = (Mat_<double>(3, 3) << 1,  0,         0,
                                         0,  cos(beta), sin(beta),
                                         0, -sin(beta), cos(beta));
    Mat R_yaw   = (Mat_<double>(3, 3) << cos(alpha), 0, -sin(alpha),
                                         0,          1, 0,
                                         sin(alpha), 0, cos(alpha));
    Mat R_roll  = (Mat_<double>(3, 3) << cos(gamma) , sin(gamma), 0,
                                         -sin(gamma), cos(gamma), 0,
                                         0,           0,          1);
    // Different orders of pitch, yaw and roll will result in different outcomes!
    return R_pitch*R_yaw*R_roll;
}

double getMax(const double a, const double b)
{
    double output;
    if (a>b)    {
        output = a;
    } else  {
        output = b;
    }
    return output;
}

double getMin(const double a, const double b)
{
    double output;
    if (a<b)    {
        output = a;
    } else  {
        output = b;
    }
    return output;
}

double calcSlope(Point2f pt1, Point2f pt2)
{
    double slope = calcDivision((pt2.y - pt1.y), (pt2.x - pt1.x));
    return slope;
}

double calcIntersect(Point2f pt1, Point2f pt2)
{
    double intersect = calcDivision((pt2.x*pt1.y - pt1.x*pt2.y), (pt2.x - pt1.x));
    return intersect;
}

Mat calcVanPts(Mat &src,  const vector<Point2f> pts, string name)
{
    int num_pts = pts.size();
    //=====Calc and draw lines=====
    double m[2], b[2];     // y = mx+b
    for(int i = 0; i<num_pts; i+=2)
    {
        int beg_pts = i, end_pts = i+1;
        drawLine( src, pts[beg_pts] , pts[end_pts], 'G');
        imshow( name, src );
        m[i/2] = calcSlope(pts[beg_pts], pts[end_pts]);
        b[i/2] = calcIntersect(pts[beg_pts], pts[end_pts]);
    } // need to protect divided by 0  TBD
    //=====Calc vanishing point=====
    Point2f vPoint;
    vPoint.x = calcDivision( (b[1]-b[0]), (m[0]-m[1]) );
    vPoint.y = calcDivision( (b[1]*m[0]-b[0]*m[1]), (m[0]-m[1]) );

    drawLine( src, pts[1] ,vPoint, 'Y');
    drawLine( src, pts[2] ,vPoint, 'R');
    imshow( name, src);

    Mat vPointMat = (Mat_<double>(3,1) << vPoint.x, vPoint.y, 1 );

    return vPointMat;
}

void calcRotAngle(const Mat &unit_vector, double &pitch_deg, double &yaw_deg)
{
    Mat u_d1 = unit_vector.clone();
    pitch_deg = asin(-u_d1.at<double>(1,0))*constant::TO_DEG;
    double tmp_y = calcDivision( u_d1.at<double>(2,0), cos(pitch_deg*constant::TO_RAD) );
    yaw_deg = acos(tmp_y)*constant::TO_DEG;
}




//----Legacy function, now is useless--------
double calcProjAngle(const Mat &direction1, const Mat &direction2, const char s)  //useless, kept as backup.
{
    Mat d1 = direction1.clone();
    Mat d2 = direction2.clone();
    switch (s) {
        case 'P':
            d1.row(0) = 0.0;
            d2.row(0) = 0.0;
            break;
        case 'Y':
            d1.row(1) = 0.0;
            d2.row(1) = 0.0;
            break;
        case 'R':
            d1.row(2) = 0.0;
            d2.row(2) = 0.0;
            break;
        default:
            break;
    }
    double cos_angle = calcDivision( d1.dot(d2), norm(d1)*norm(d2) );
    double angle = acos(cos_angle)*constant::TO_DEG;
    return angle;
}

Mat calcCurl(const Mat &m1, const Mat &m2)
{
    Mat curl = (Mat_<double>(3,1) << m1.at<double>(1,0)*m2.at<double>(2,0) - m1.at<double>(2,0)*m2.at<double>(1,0),
                                     m1.at<double>(2,0)*m2.at<double>(0,0) - m1.at<double>(0,0)*m2.at<double>(2,0),
                                     m1.at<double>(0,0)*m2.at<double>(1,0) - m1.at<double>(1,0)*m2.at<double>(0,0)  );
    return curl;
}
