#ifndef SCALE_ESTIMATION_H
#define SCALE_ESTIMATION_H

#include "system.h"

class SacleEstimation : public System
{
public:
    // Constructor and Destructor.
    SacleEstimation(calibration params_camera_internal);
    ~SacleEstimation();

    // Start the process sequence for a new image.
    bool process (Mat &img);

private:
    calibration params;

    void getRollByVanLine(Mat &img);
};

#endif // SCALE_ESTIMATION_H
