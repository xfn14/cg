#include "point.h"

float Point::getX(){
    return Point::x;
}

float Point::getY(){
    return Point::y;
}

float Point::getZ(){
    return Point::z;
}

void Point::setX(float a){
    Point::x = a;
}

void Point::setY(float b){
    Point::y = b;
}

void Point::setZ(float c){
    Point::z = c;
}

void Point::addX(float a){
    Point::x += a;
}

void Point::addY(float b){
    Point::y += b;
} 

void Point::addZ(float c){
    Point::z += c;
}
