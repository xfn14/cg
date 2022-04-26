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
