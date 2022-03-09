#include "patch.h"

Patch::Patch(){
}

void Patch::addPoint(Point point) {
    controlPoints.push_back(point);
}

vector<Point> Patch::getPoints() {
    return controlPoints;
}