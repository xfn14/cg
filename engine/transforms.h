#ifndef _TRANSFORMS_
#define _TRANSFORMS_

#include <iostream>
#include <vector>
#include <string>

#include "../utils/point.h"

using namespace std;

class Translate {
    private:
        float x, y, z;
        vector<Point> path;

    public:
        Translate(float i, float j, float u) {
            Translate::x = i;
            Translate::y = j;
            Translate::z = u;
        }
        float getX();
        float getY();
        float getZ();
        void addPoint(Point p);
        vector<Point> getPath(int time, bool align);
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

class Color {
    private:
        float r, g, b;

    public:
        Color() {
            Color::r = 0.5;
            Color::g = 0.5;
            Color::b = 0.5;
        }
        Color(float i, float j, float u) {
            Color::r = i;
            Color::g = j;
            Color::b = u;
        }
        float getR();
        float getG();
        float getB();
};

#endif
