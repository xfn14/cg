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

void Patch::addTexture(Point point) {
    Patch::textures.push_back(point);
}

vector<Point> Patch::getTexture() {
    return Patch::textures;
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
    int j = 0;
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

vector<Point> Patch::tessellate(int level) {
    vector<Point> res;
    float tessel = 1.0f/ (float) level;
    for(int i = 0; i < level; i++) {
        for(int j = 0; j < level; j++) {
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

            float vector1[3], vector2[3], normal[3];
            float x[3] = {p0.getX(),p0.getY(),p0.getZ()};
            float y[3] = {p1.getX(),p1.getY(),p1.getZ()};
            float z[3] = {p2.getX(),p2.getY(),p2.getZ()};
            float w[3] = {p3.getX(),p3.getY(),p3.getZ()};

            toVector(x,z,vector1);
            toVector(x,w,vector2);
            cross(vector1,vector2,normal);
            normalize(normal);
            Point n = *(new Point(normal[0], normal[1], normal[2]));

            normals.push_back(n);
            normals.push_back(n);
            normals.push_back(n);

            textures.push_back(*(new Point(0,0,0)));
            textures.push_back(*(new Point(1,0,0)));
            textures.push_back(*(new Point(1,1,0)));

            toVector(x,w,vector1);
            toVector(x,y,vector2);
            cross(vector1,vector2,normal);
            normalize(normal);
            Point m = *(new Point(normal[0], normal[1], normal[2]));

            normals.push_back(m);
            normals.push_back(m);
            normals.push_back(m);


            textures.push_back(*(new Point(0,0,0)));
            textures.push_back(*(new Point(1,0,0)));
            textures.push_back(*(new Point(0,1,0)));

        }
    }
    return res;
}
