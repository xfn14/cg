#ifndef _BEZIER_PATCH_
#define _BEZIER_PATCH_

#include <iostream>
#include <vector>

#include "point.h"

using namespace std;

class Patch {
    private:
        vector<Point> controlPoints;

    public:
        void addPoint(Point);
        vector<Point> getPoints();
        vector<vector<int>> tessellate(int level);
};

#endif