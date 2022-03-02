#ifndef _POINT_H_
#define _POINT_H_

#include <math.h>
#include <string>

using namespace std;

class Point{
    float x;
    float y;
    float z;

    public:
        Point();
        Point(float, float, float);
        float getX();
        float getY();
        float getZ();
        void setX(float);
        void setY(float);
        void setZ(float);
};

#endif