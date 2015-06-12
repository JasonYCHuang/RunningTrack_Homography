#include "scale_estimation.h"

SacleEstimation::SacleEstimation (calibration params_camera_internal) : params(params_camera_internal)  {}

SacleEstimation::~SacleEstimation() {}

bool SacleEstimation::process (Mat &img)
{
    // 1. Calculate the roll angle by the vanishing line.

    // 2. Rotate image by the roll angle, and the vanishing line is parallel to horizontal.

    // 3. Calculate pitch and yaw angles by the vanishing points.

    // 4. Get the bird view base on pitch and yaw angles.

}


void SacleEstimation::getRollByVanLine(Mat &img)
{
    // Fetch feature points "manually".
    vector<Point2f> selected_pts(8);
    getPtsLoc(img, selected_pts, name);
    // Picks the fisrt 4 pts for the vanishing point, since we get it from two lines.
    // Need to update VP calculation by using all points!. TBD
    vector<Point2f> selected_pts_for_vp{selected_pts[0], selected_pts[1], selected_pts[2], selected_pts[3]};

    // Calculate the vanishing point
    Mat vanishingPoint = calcVanPts(img, selected_pts_for_vp, name);

    // Calculate and draw the vanishing line
    Mat vanishingLine = calcVanLineSVD(selected_pts, img, "vLine", 'R');

    // Calculate the surface normal
    Mat N = (K.t())*(vanishingLine);
    N = N/norm(N);
    // //cout << "normal" << N << endl << endl;

    // Calculate the rotaion matrix base on MVA2011 IAPR Conference "An efficient algorithm for UAV indoor pose estimation using vanishing geometry".
    Mat R1, R2, R3;
    R1 = (K.inv()) * vanishingPoint / norm( (K.inv())*vanishingPoint );
    R3 = (K.t()) * vanishingLine / norm( (K.t())*vanishingLine );
    R2 = R1.cross(R3);
    // //cout << "R1" << R1 << endl;
    // //cout << "R2" << R2 << endl;
    // //cout << "R3" << R3 << endl;
    }
    waitKey(0);
    destroyAllWindows();
}
