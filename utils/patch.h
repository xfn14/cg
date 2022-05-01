#ifndef _BEZIER_PATCH_
#define _BEZIER_PATCH_

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include "matrix.h"

#include "point.h"

using namespace std;

class Patch {
    private:
        vector<Point> controlPoints;
        vector<Point> normals;


public:
        void addPoint(Point);
        vector<Point> getPoints();
        vector<Point> tessellate(int level);
};

#endif