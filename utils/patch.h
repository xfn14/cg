#ifndef _BEZIER_PATCH_
#define _BEZIER_PATCH_

#include <iostream>

#include "vector"
#include "point.h"

using namespace std;

class Patch {
    vector<Point*> points;

    public:
        void addPoint(Point*);
        vector<Point*> getPoints();
};

#endif