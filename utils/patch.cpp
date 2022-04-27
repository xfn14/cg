#include "patch.h"

void Patch::addPoint(Point point) {
    controlPoints.push_back(point);
}

vector<Point> Patch::getPoints() {
    return controlPoints;
}

// Tessellate the bezier patch
vector<vector<int>> Patch::tessellate(int level) {
    vector<vector<int>> triangles;
    int i, j, k, l;

    for(i = 0; i < level; ++i) {
        vector<vector<int>> newTriangles;
        for(j = 0; j < triangles.size(); ++j) {
            vector<int> triangle = triangles[j];
            for(k = 0; k < 3; ++k) {
                Point p1 = controlPoints[triangle[k]];
                Point p2 = controlPoints[triangle[(k+1)%3]];
                Point p3 = controlPoints[triangle[(k+2)%3]];

                Point p4 = Point(p1.getX() + (p2.getX() - p1.getX())/3, p1.getY() + (p2.getY() - p1.getY())/3, p1.getZ() + (p2.getZ() - p1.getZ())/3);
                Point p5 = Point(p2.getX() + (p3.getX() - p2.getX())/3, p2.getY() + (p3.getY() - p2.getY())/3, p2.getZ() + (p3.getZ() - p2.getZ())/3);
                Point p6 = Point(p4.getX() + (p5.getX() - p4.getX())/3, p4.getY() + (p5.getY() - p4.getY())/3, p4.getZ() + (p5.getZ() - p4.getZ())/3);

                int p7 = controlPoints.size();
                controlPoints.push_back(p4);
                int p8 = controlPoints.size();
                controlPoints.push_back(p5);
                int p9 = controlPoints.size();
                controlPoints.push_back(p6);

                vector<int> triangle1 = {triangle[k], p7, p9};
                vector<int> triangle2 = {p7, triangle[(k+1)%3], p8};
                vector<int> triangle3 = {p9, p8, triangle[(k+2)%3]};
                vector<int> triangle4 = {p7, p8, p9};

                newTriangles.push_back(triangle1);
                newTriangles.push_back(triangle2);
                newTriangles.push_back(triangle3);
                newTriangles.push_back(triangle4);
            }
        }
        triangles = newTriangles;
    }

    return triangles;
}