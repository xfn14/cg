#include "transforms.h"

float Translate::getX() {
    return Translate::x;
}

float Translate::getY() {
    return Translate::y;
}

float Translate::getZ() {
    return Translate::z;
}

void Translate::addPoint(Point p) {
    Translate::path.push_back(p);
}

vector<Point> Translate::getPath(int time, bool align) {
    int n = Translate::path.size();
    for(int i = 0; i < n; i++) {
        Point p = Translate::path[i];
        Point p0 = (i == 0) ? Translate::path[0] : Translate::path[i - 1];
        Point p1 = Translate::path[i];
        Point p2 = (i == n - 1) ? Translate::path[n - 1] : Translate::path[i + 1];
        Point p3 = (i == n - 1) ? Translate::path[n - 1] : Translate::path[i + 2];
        float t2 = time * time;
        float t3 = t2 * time;
        float x = 0.5 * ((2 * p1.getX()) + (-p0.getX() + p2.getX()) * time + (2 * p0.getX() - 5 * p1.getX() + 4 * p2.getX() - p3.getX()) * t2 + (-p0.getX() + 3 * p1.getX() - 3 * p2.getX() + p3.getX()) * t3);
        float y = 0.5 * ((2 * p1.getY()) + (-p0.getY() + p2.getY()) * time + (2 * p0.getY() - 5 * p1.getY() + 4 * p2.getY() - p3.getY()) * t2 + (-p0.getY() + 3 * p1.getY() - 3 * p2.getY() + p3.getY()) * t3);
        float z = 0.5 * ((2 * p1.getZ()) + (-p0.getZ() + p2.getZ()) * time + (2 * p0.getZ() - 5 * p1.getZ() + 4 * p2.getZ() - p3.getZ()) * t2 + (-p0.getZ() + 3 * p1.getZ() - 3 * p2.getZ() + p3.getZ()) * t3);
        Point p_new = Point(x, y, z);
        path.push_back(p_new);
    }
    return path;
}

float Rotate::getAngle() {
    return Rotate::angle;
}

float Rotate::getX() {
    return Rotate::x;
}

float Rotate::getY() {
    return Rotate::y;
}

float Rotate::getZ() {
    return Rotate::z;
}

float Scale::getX() {
    return Scale::x;
}

float Scale::getY() {
    return Scale::y;
}

float Scale::getZ() {
    return Scale::z;
}

float Color::getR() {
    return Color::r;
}

float Color::getG() {
    return Color::g;
}

float Color::getB() {
    return Color::b;
}
