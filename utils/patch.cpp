#include "patch.h"

void Patch::addPoint(Point *point) {
    controlPoints.push_back(point);
}

vector<Point*> Patch::getPoints() {
    return controlPoints;
}