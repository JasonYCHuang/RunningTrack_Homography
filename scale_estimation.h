#ifndef SCALE_ESTIMATION_H
#define SCALE_ESTIMATION_H

#include "system.h"
#include "line2d.h"

class SacleEstimation : public System
{
public:
    // Constructor and Destructor.
    SacleEstimation(calibration params_1, setting params_2);
    ~SacleEstimation();

    // Start the process sequence for a new image.
    bool process (Mat &img);


private:
    // Configuration parameters.
    calibration params_calib;
    setting params_setting;

    // step1. Calculate the roll angle by the vanishing line.
    double getRollByVanLine(Mat &img, Mat &v_point);
    Mat calcVanLineSVD(const vector<Point2f> &pts, Mat &img, string title, const char color, double &roll_deg);

    // step2. Rotate image by the roll angle, and the vanishing line is parallel to horizontal.
    // step4. Get the bird view base on pitch and yaw angles.
    void rotateView(Mat &img_ori, Mat &img_transformed, double pitch_deg, double yaw_deg, double roll_deg, string img_name, bool is_bird_view);
    map<string, double> getBoundary(const vector<Point2f> &corners);

    // step3. Calculate pitch and yaw angles by the vanishing points.
    void getPitchYawByVanPoint(Mat &v_point, double &pitch_deg, double &yaw_deg);
};

#endif // SCALE_ESTIMATION_H
