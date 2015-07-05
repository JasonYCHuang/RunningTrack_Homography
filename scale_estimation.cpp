#include "scale_estimation.h"

using namespace cv;

SacleEstimation::SacleEstimation (calibration params_1, setting params_2) : params_calib(params_1), params_setting(params_2)  {}

SacleEstimation::~SacleEstimation() {}

bool SacleEstimation::process (Mat &img)
{
    // step1. Calculate the roll angle by the vanishing line.
    Mat img_step_1 = img.clone();
    Mat v_point;
    double roll_angle_deg = getRollByVanLine(img_step_1, v_point);
    waitKey(0);
    destroyAllWindows();

    // step2. Rotate image by the roll angle, and the vanishing line is parallel to horizontal.
    Mat img_step_2 = img.clone();
    Mat img_step_2_horizon;
    rotateView(img_step_2, img_step_2_horizon, 0, 0, roll_angle_deg, "Horizon", false);
    waitKey(0);
    destroyAllWindows();

    // step3. Calculate pitch and yaw angles by the vanishing points.
    double pitch_angle_deg, yaw_angle_deg;
    getPitchYawByVanPoint(v_point, pitch_angle_deg, yaw_angle_deg);
    waitKey(0);
    destroyAllWindows();

    // step4. Align to track center, i.e. rotated by yaw angle.
    Mat img_step_4 = img_step_2_horizon.clone();
    Mat img_step_4_align;
    rotateView(img_step_4, img_step_4_align, 0, yaw_angle_deg, 0, "Align", false);
    waitKey(0);
    destroyAllWindows();

    // step5. Get the bird view base on pitch angles.
    Mat img_step_5 = img_step_4_align.clone();
    Mat img_step_5_bird_view;
    rotateView(img_step_5, img_step_5_bird_view, (pitch_angle_deg-90), 0, 0, "Bird view", true);
    waitKey(0);
    destroyAllWindows();

    /*
     *     // step3. Calculate pitch and yaw angles by the vanishing points.
    double pitch_angle_deg, yaw_angle_deg;
    getPitchYawByVanPoint(v_point, pitch_angle_deg, yaw_angle_deg);
    waitKey(0);
    destroyAllWindows();

    // step4. Align to track center, i.e. rotated by yaw angle.
    Mat img_step_4 = img_step_2_horizon.clone();
    Mat img_step_4_align;
    rotateView(img_step_4, img_step_4_align, 0, yaw_angle_deg, 0, "Align", false);
    waitKey(0);
    destroyAllWindows();

    // step5. Get the bird view base on pitch angles.
    Mat img_step_5 = img_step_4_align.clone();
    Mat img_step_5_bird_view;
    rotateView(img_step_5, img_step_5_bird_view, (pitch_angle_deg-90), 0, 0, "Bird view", true);
    waitKey(0);
    destroyAllWindows();

    */


    cout << "pitch_angle_deg: " << pitch_angle_deg << endl;
    cout << "yaw_angle_deg: "   << yaw_angle_deg << endl;
    cout << "roll_angle_deg: "  << roll_angle_deg << endl;

    return true;
}

// ---------------------------------------------------------------------
// step3. Calculate pitch and yaw angles by the vanishing points.
void SacleEstimation::getPitchYawByVanPoint(Mat &v_point, double &pitch_deg, double &yaw_deg)
{
    // Set homogeneous coordinate of the vanishing point and camera center
    Mat v_track_line    = v_point;      //location of the vanishing point on the image.
    Mat v_camera_center = (Mat_<double>(3, 1) << params_calib.center.x, params_calib.center.y, 1); //location of the camera center on the image.

    // Camera internal parameter
    Mat K = params_calib.K.clone();
    Mat inv_K;
    invert(K, inv_K);

    // v=Kd     // a vanishing point "v" back-projects to a ray with direction d.
    Mat d_track_line    = inv_K*v_track_line;
    Mat d_camera_center = inv_K*v_camera_center;
    d_track_line = d_track_line/norm(d_track_line);           //normalized as a unit vector
    d_camera_center = d_camera_center/norm(d_camera_center);  //normalized as a unit vector
    // //cout << d_track_line << endl;
    // //cout << d_camera_center << endl;

    // Calculate the angle between the 2 vectors. [1]sport track lines direction. [2]camera center pointing direction.
    Mat v = d_track_line.cross(d_camera_center);      // v = A.cross(B) = |A|*|B|*sin(theta)
    double sin = norm(v);                             // Since d_track_line and d_camera_center are unit vectors, xross magnitude is equal to sin.
    double cos = d_track_line.dot(d_camera_center);       // Since d_track_line and d_camera_center are unit vectors, dot magnitude is equal to cos.

    Mat vx =  (Mat_<double>(3,3) <<    0,                   -v.at<double>(2,0),  v.at<double>(1,0),
                                       v.at<double>(2,0),   0,                  -v.at<double>(0,0),
                                      -v.at<double>(1,0),   v.at<double>(0,0),   0                 );

    Mat R = Mat::eye(3, 3, CV_64F) + vx + vx*vx*((1-cos)/(sin*sin));   //http://math.stackexchange.com/questions/180418/calculate-rotation-matrix-to-align-vector-a-to-vector-b-in-3d

    // Calculate Pitch, Yaw angles base on Roll=0.
    calcRotAngle(d_track_line, pitch_deg, yaw_deg);   //calc angle from rotation matrix.
}


// ---------------------------------------------------------------------
// step2. Rotate image by the roll angle, and the vanishing line is parallel to horizontal.
// step4. Get the bird view base on pitch and yaw angles.

void SacleEstimation::rotateView(Mat &img_ori, Mat &img_transformed, double pitch_deg, double yaw_deg, double roll_deg, string img_name, bool is_bird_view)
{
    // Setting the rotation Matrix  // getRotationMatrix(yaw, pitch, roll)
    Mat R = getRotationMatrix(yaw_deg*constant::TO_RAD, pitch_deg*constant::TO_RAD, roll_deg*constant::TO_RAD);

    // Homography matrix calculated from pure rotation.
    Mat K = params_calib.K.clone();
    Mat H = K*R*K.inv();

    // create the image with rotation.
    // Calculate the amount to shift the image to field of view by corners.
    // Caution: This shift mechanism will be failure when the homography of the 4 corners swapped orders!
    vector<Mat> img_corners_coordinate{ (Mat_<double>(3, 1) << 0, 0, 1),
                                        (Mat_<double>(3, 1) << 0, img_ori.size().height, 1),
                                        (Mat_<double>(3, 1) << img_ori.size().width, img_ori.size().height, 1),
                                        (Mat_<double>(3, 1) << img_ori.size().width, 0, 1) };// The homogeneous coordinate of the original image.
    vector<Point2f> img_corners_transformed;    // Transformed image corners.
    for(auto &i : img_corners_coordinate)    {
        i = H*i;        // Homography transformation.
        img_corners_transformed.push_back(Point2f(i.at<double>(0, 0)/i.at<double>(2, 0), i.at<double>(1, 0)/i.at<double>(2, 0)));
        // cout << "img_corners_transformed" << Point2f(i.at<double>(0, 0)/i.at<double>(2, 0), i.at<double>(1, 0)/i.at<double>(2, 0)) << endl;
    }
    map<string, double> boundary = getBoundary(img_corners_transformed);      // The boundary of transformed image corners.

    // Modify Homography Matrix to shift the image into the field of view.
    Mat shift;
    Size new_img_size;
    if (is_bird_view)   {
        shift = (Mat_<double>(3, 3) << 1, 0, -(img_corners_transformed[2].x-boundary["width"]*0.7),
                                       0, 1, -(img_corners_transformed[2].y-boundary["height"]*1.3),
                                       0, 0, 1);
        new_img_size = Size(boundary["width"]*1.2, boundary["height"]*1.3);
        H = shift*H;    // Update Homography base on a shift, i.e. multiplied by a translation matrix.
    }

    /* else  {
        shift = (Mat_<double>(3, 3) << 1, 0, -boundary["left"],
                                       0, 1, -boundary["top"],
                                       0, 0, 1);
        new_img_size = Size(boundary["width"], boundary["height"]);
        H = shift*H;    // Update Homography base on a shift, i.e. multiplied by a translation matrix.

    }*/

    // Perspective transformation.
    warpPerspective(img_ori, img_transformed, H, new_img_size);

    // Display and save images
    namedWindow( img_name, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO );
    imshow( img_name, img_transformed );
    imwrite( "./" + img_name + ".jpg", img_transformed );
}

map<string, double> SacleEstimation::getBoundary(const vector<Point2f> &corners)
{
    map<string, double> boundary;
    for(unsigned int j=0; j!=corners.size(); ++j)    {
        if(boundary.empty())    {      // Initialized boundary if there is no data.
            boundary["left"]   = corners[j].x;
            boundary["right"]  = corners[j].x;
            boundary["top"]    = corners[j].y;
            boundary["bottom"] = corners[j].y;
        } else  {                      // Compare corners to get the outer-most boundary.
            boundary["left"]   = getMin(boundary["left"], corners[j].x);
            boundary["right"]  = getMax(boundary["right"], corners[j].x);
            boundary["top"]    = getMin(boundary["top"], corners[j].y);
            boundary["bottom"] = getMax(boundary["bottom"], corners[j].y);
        }
    }
    // Calculate width and height
    boundary["width"]  = boundary["right"] - boundary["left"];
    boundary["height"] = boundary["bottom"] - boundary["top"];

    return boundary;
}

// ---------------------------------------------------------------------
// step1. Calculate the roll angle by the vanishing line.
double SacleEstimation::getRollByVanLine(Mat &img, Mat &v_point)
{
    string name = "step1. Calculate the roll angle by the vanishing line.";
    // Fetch feature points "manually".
    vector<Point2f> selected_pts( (params_setting.num_lines_for_vline)*2 );
    getPtsLoc(img, selected_pts, name);
    // Picks the fisrt 4 pts for the vanishing point, since we get it from two lines.
    // Need to update VP calculation by using all points!. TBD
    vector<Point2f> selected_pts_for_vp{selected_pts[2], selected_pts[3], selected_pts[4], selected_pts[5]};

    // Calculate the vanishing point
    v_point = calcVanPts(img, selected_pts_for_vp, name);

    // Calculate and draw the vanishing line
    double roll_deg;
    Mat v_line = calcVanLineSVD(selected_pts, img, "vLine", 'R', roll_deg);

    // Calculate the surface normal
    Mat K = params_calib.K.clone();
    Mat N = (K.t())*(v_line);
    N = N/norm(N);
    // //cout << "normal" << N << endl << endl;

    // Calculate the rotaion matrix base on MVA2011 IAPR Conference "An efficient algorithm for UAV indoor pose estimation using vanishing geometry".
    Mat R1, R2, R3;
    R1 = (K.inv()) * v_point / norm( (K.inv())*v_point );
    R3 = (K.t()) * v_line / norm( (K.t())*v_line );
    R2 = R1.cross(R3);

    return roll_deg;
}

Mat SacleEstimation::calcVanLineSVD(const vector<Point2f> &pts, Mat &img, string title, const char color, double &roll_deg)
{
    // Set Mat for SVD: A=U*D*VT
    Mat A, U, D, VT, V;

    // Convert points to lines, and create A matrix by vanishing-line equations using DLT formulas.
    vector<Line2D> track_line(pts.size()/2);
    for (unsigned int i=0; i<track_line.size(); ++i)    {
        track_line[i].setLineParams(pts[i*2], pts[i*2+1], (1+i));
        Mat temp1 = (Mat_<double>(1,6) << 0, 0, -track_line[i].lamb(), -1, track_line[i].lamb()*track_line[i].b(), track_line[i].b());
        Mat temp2 = (Mat_<double>(1,6) << track_line[i].lamb(), 1, 0, 0, -track_line[i].lamb()*track_line[i].a(), -track_line[i].a());
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
    line(img, one, two, colorScalar(color), 1, 8, 0);
    imshow( title, img );
    imwrite( "./vLine.png", img );
    roll_deg = -(v_line.at<double>(0,0) / v_line.at<double>(1,0))*constant::TO_DEG;
    //cout << "roll(deg): " << roll_deg;

    return v_line;
}

