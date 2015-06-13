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
    calibration params_calib;
    setting params_setting;

    double getRollByVanLine(Mat &img);
    Mat calcVanLineSVD(const vector<Point2f> &pts, Mat &img, string title, const char color, double &roll_angle_deg);

};

#endif // SCALE_ESTIMATION_H
