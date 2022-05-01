#ifndef _BEZIER_PATCH_
#define _BEZIER_PATCH_

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>

#include "point.h"

using namespace std;

class Patch {
    private:
        vector<Point> controlPoints;
        vector<Point> normals;
        
    public:
        void addPoint(Point);
        vector<Point> getPoints();
        void addNormals(Point);
        vector<Point> getNormals();
        vector<Point> tessellate(int level);
};

#endif