#ifndef PROBIRDVIEW
#define PROBIRDVIEW

#include "lib_misc.h"
#include "lib_math.h"

using namespace cv;
using namespace std;

map<string, double> getBoundary(const vector<Point2f> &corners);
Mat translateImg(Mat &img, int offsetx, int offsety);
void proBirdView();
void birdView(const string name_ori);



















#endif // PROBIRDVIEW

