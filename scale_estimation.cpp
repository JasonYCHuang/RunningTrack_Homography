#include "scale_estimation.h"

SacleEstimation::SacleEstimation (calibration params_1, setting params_2) : params_calib(params_1), params_setting(params_2)  {}

SacleEstimation::~SacleEstimation() {}

bool SacleEstimation::process (Mat &img)
{
    // 1. Calculate the roll angle by the vanishing line.
    double roll_angle_deg = getRollByVanLine(img);
    waitKey(0);
    destroyAllWindows();

    // 2. Rotate image by the roll angle, and the vanishing line is parallel to horizontal.

    // 3. Calculate pitch and yaw angles by the vanishing points.

    // 4. Get the bird view base on pitch and yaw angles.

}

double SacleEstimation::getRollByVanLine(Mat &img)
{
    string name = "step1. find the roll by the vanishing line.";
    // Fetch feature points "manually".
    vector<Point2f> selected_pts( (this->params_setting.num_lines_for_vline)*2 );
    getPtsLoc(img, selected_pts, name);
    // Picks the fisrt 4 pts for the vanishing point, since we get it from two lines.
    // Need to update VP calculation by using all points!. TBD
    vector<Point2f> selected_pts_for_vp{selected_pts[0], selected_pts[1], selected_pts[2], selected_pts[3]};

    // Calculate the vanishing point
    Mat vanishing_point = calcVanPts(img, selected_pts_for_vp, name);

    // Calculate and draw the vanishing line
    double roll_angle_deg;
    Mat vanishing_line = calcVanLineSVD(selected_pts, img, "vLine", 'R', roll_angle_deg);

    // Calculate the surface normal
    Mat N = (K.t())*(vanishing_line);
    N = N/norm(N);
    // //cout << "normal" << N << endl << endl;

    // Calculate the rotaion matrix base on MVA2011 IAPR Conference "An efficient algorithm for UAV indoor pose estimation using vanishing geometry".
    Mat R1, R2, R3;
    R1 = (K.inv()) * vanishing_point / norm( (K.inv())*vanishing_point );
    R3 = (K.t()) * vanishing_line / norm( (K.t())*vanishing_line );
    R2 = R1.cross(R3);

    return roll_angle_deg;
}


Mat SacleEstimation::calcVanLineSVD(const vector<Point2f> &pts, Mat &img, string title, const char color, double &roll_angle_deg)
{
    // Set Mat for SVD: A=U*D*VT
    Mat A, U, D, VT, V;

    // Convert points to lines, and create A matrix by vanishing-line equations using DLT formulas.
    vector<Line2D> line(pts.size()/2);
    for (unsigned int i=0; i<line.size(); ++i)    {
        line[i].setLineParams(pts[i*2], pts[i*2+1], (1+i));
        Mat temp1 = (Mat_<double>(1,6) << 0, 0, -line[i].lamb(), -1, line[i].lamb()*line[i].b(), line[i].b());
        Mat temp2 = (Mat_<double>(1,6) << line[i].lamb(), 1, 0, 0, -line[i].lamb()*line[i].a(), -line[i].a());
        A.push_back(temp1);
        A.push_back(temp2);
    }

    // Solve SVD. vLine is equal to the 1st row of A.
    SVD::compute(A, D, U, VT);
    V = VT.t();
    // Normalized vLine. That is: vLine = [a, b, c].t()    line-eq: ax+by+c=0  //  normalized: vLine = [A, B, 1].t()    line-eq: Ax+By+1=0
    Mat v_line = (Mat_<double>(3,1) << V.at<double>(0,5)/V.at<double>(4,5), V.at<double>(2,5)/V.at<double>(4,5), 1 );

    // Determine 2 points for vLine, and draw the vanishing line base on them.
    Point2f one, two;
    one.x = 200;
    two.x = 1400;
    one.y = -( v_line.at<double>(2,0) + v_line.at<double>(0,0)*one.x ) / v_line.at<double>(1,0) ;  // y=mx+d   m=-a/b, d=-c/b
    two.y = -( v_line.at<double>(2,0) + v_line.at<double>(0,0)*two.x ) / v_line.at<double>(1,0) ;
    // Make a shift to ensure the vanishing line is in the field of view.
    double shift;
    if(one.y<0 || two.y<0)  {
        shift = (one.y < two.y) ? -one.y : -two.y;
    }   // Need to amend the case when vLine is at bottom of the image! TBD
    one.y += shift;
    two.y += shift;

    // Draw the vanishing line
    drawLine( img, one, two, color );
    imshow( title, img );
    imwrite( "./vLine.png", img );
    roll_angle_deg = -(v_line.at<double>(0,0) / v_line.at<double>(1,0))*constant::TO_DEG;
    //cout << "roll(deg): " << roll_angle_deg;

    return v_line;
}
