#ifndef _TRANSFORMS_
#define _TRANSFORMS_

#include <string>

using namespace std;

class Translate {
    private:
        float x, y, z;

    public:
        Translate(float i, float j, float u) {
            Translate::x = i;
            Translate::y = j;
            Translate::z = u;
        }
        float getX();
        float getY();
        float getZ();
};

class Rotate {
    private:
        float angle, x, y, z;

    public:
        Rotate(float a, float i, float j, float u) {
            Rotate::angle = a;
            Rotate::x = i;
            Rotate::y = j;
            Rotate::z = u;
        }
        float getAngle();
        float getX();
        float getY();
        float getZ();
};

class Scale {
    private:
        float x, y, z;

    public:
        Scale(float i, float j, float u) {
            Scale::x = i;
            Scale::y = j;
            Scale::z = u;
        }
        float getX();
        float getY();
        float getZ();
};

#endif