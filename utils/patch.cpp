#include "patch.h"

void Patch::addPoint(Point point) {
    Patch::controlPoints.push_back(point);
}

vector<Point> Patch::getPoints() {
    return Patch::controlPoints;
}

void Patch::addNormals(Point point) {
    Patch::normals.push_back(point);
}

vector<Point> Patch::getNormals() {
    return Patch::normals;
}

float binomial(int n, int k) {
    if(k == 0 || k == n) return 1;
    else return binomial(n-1, k-1) + binomial(n-1, k);
}

float bernstein(int m, int n, float t) {
    float b = 0;
    for(int i = 0; i <= m; ++i) {
        float c = binomial(m, i);
        b += c * pow(t, i) * pow(1-t, m-i);
    }
    return b;
}

Point bezierCurve(float t, Point p0, Point p1, Point p2, Point p3){
    Point p;

    float a0, a1, a2, a3;
    a0 = pow((1-t),3);
    a1 = 3 * pow((1-t),2) * t;
    a2 = 3 * (1-t) * pow(t,2);
    a3 = pow(t,3);

    p.setX(a0 * p0.getX() + a1 * p1.getX() + a2 * p2.getX() + a3 * p3.getX());
    p.setY(a0 * p0.getY() + a1 * p1.getY() + a2 * p2.getY() + a3 * p3.getY());
    p.setZ(a0 * p0.getZ() + a1 * p1.getZ() + a2 * p2.getZ() + a3 * p3.getZ());
    return p;

}

Point determineSection(float u, float v, const vector<Point> controlPoints){
    int j = 1;
    vector<Point> curve, matrix;
    for(int i=0; i < 16; i++){
        matrix.push_back(controlPoints[i]);
        j++;
        if(j % 4 == 0){
            Point point = bezierCurve(u, matrix[0],matrix[1],matrix[2],matrix[3]);
            matrix.clear();
            curve.push_back(point);
            j = 0;
        }
    }
    return bezierCurve(v, curve[0], curve[1], curve[2], curve[3]);
}

void cross(Point a, Point b, Point res) {
    res.setX(a.getY()*b.getZ() - a.getZ()*b.getY());
    res.setY(a.getZ()*b.getX() - a.getX()*b.getZ());
    res.setZ(a.getX()*b.getY() - a.getY()*b.getX());
}

vector<Point> Patch::tessellate(int level) {
    vector<Point> res;
    float tessel = 1.0f/ (float) level;
    for(int i = 0; i < level; ++i) {
        for(int j = 0; j < level; ++j) {
            Point p0, p1, p2, p3;
            p0 = determineSection((float) i*tessel,(float) j*tessel,controlPoints);
            p1 = determineSection((float) i*tessel,(float) (j+1)*tessel,controlPoints);
            p2 = determineSection((float) (i+1)*tessel,(float) j*tessel,controlPoints);
            p3 = determineSection((float) (i+1)*tessel,(float) (j+1)*tessel,controlPoints);

            res.push_back(p0);
            res.push_back(p2);
            res.push_back(p3);

            res.push_back(p0);
            res.push_back(p3);
            res.push_back(p1);


        }
    }
    return res;
}
