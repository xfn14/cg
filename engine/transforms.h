#ifndef _TRANSFORMS_
#define _TRANSFORMS_

#include <iostream>
#include <vector>
#include <string>

#include "../utils/point.h"
#include "../utils/matrix.h"

using namespace std;

class Translate {
    private:
        float x, y, z, time;
        bool align;
        vector<Point> path;

    public:
        Translate() {

        }
        
        Translate(float i, float j, float u) {
            Translate::x = i;
            Translate::y = j;
            Translate::z = u;
            Translate::time = -1;
            Translate::align = false;
        }

        Translate(float t) {
            Translate::x = -1;
            Translate::y = -1;
            Translate::z = -1;
            Translate::time = t;
            Translate::align = false;
        }

        Translate(float t, bool align) {
            Translate::x = -1;
            Translate::y = -1;
            Translate::z = -1;
            Translate::time = t;
            Translate::align = align;
        }

        float getX();
        float getY();
        float getZ();
        float getTime();
        bool getAlign();
        void addPoint(Point p);
        void drawCatmullRomCurve();
        void getGlobalCatmullRomPoint(float gt, float *point, float *deriv);
        void getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float *pos, float *deriv);
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
