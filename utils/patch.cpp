#include "patch.h"

void Patch::addPoint(Point point) {
    controlPoints.push_back(point);
}

vector<Point> Patch::getPoints() {
    return controlPoints;
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
    a1 = pow((1-t),2) * t;
    a2 = (1-t) * pow(t,2);
    a3 = pow(t,3);

    p.setX(a0 * p0.getX() + a1 * p1.getX() + a2 * p2.getX() + a3 * p3.getX());
    p.setY(a0 * p0.getY() + a1 * p1.getY() + a2 * p2.getY() + a3 * p3.getY());
    p.setZ(a0 * p0.getZ() + a1 * p1.getZ() + a2 * p2.getZ() + a3 * p3.getZ());
    return p;

}

Point determineSection(float u, float v, const vector<Point> controlPoints, int p){

    vector<Point> curve;

            Point point = bezierCurve(u, controlPoints[p],controlPoints[p+1],controlPoints[p+2],controlPoints[p+3]);
            curve.push_back(point);


    bezierCurve(v, curve[0], curve[1], curve[2], curve[3]);
}

vector<Point> Patch::tessellate(int level) {
    vector<Point> res;
    float tessel = 1.0f/ (float) level;
    for(int i = 0; i < level; ++i) {
        for(int j = 0; j < level; ++j) {
            Point p0, p1, p2, p3;
            p0 = determineSection((float) i*tessel,(float) j*tessel,controlPoints, 0);
            p1 = determineSection((float) (i+1)*tessel,(float) j*tessel,controlPoints, 4);
            p2 = determineSection((float) i*tessel,(float) (j+1)*tessel,controlPoints, 8);
            p3 = determineSection((float) (i+1)*tessel,(float) (j+1)*tessel,controlPoints, 12);

            res.push_back(p0);
            res.push_back(p1);
            res.push_back(p3);

            res.push_back(p0);
            res.push_back(p3);
            res.push_back(p2);
        }
    }
    return res;
}





// Tessellate the bezier patch into vector of Points
//vector<Point> Patch::tessellate(int level) {
//    Point points[level+1][level+1];
//    vector<Point> res;
//    int i, j, m, n;
//    for(i = 0; i < level; ++i) {
//        float u = float(i) / (float) level;
//        vector<Point> crt(32);
//        for(j = 0; j < level; ++j) {
//            float v = float(j) / (float) level;
//            Point point;
//            for(m = 0; m < 4; ++m) {
//                for(n = 0; n < 4; ++n) {
//                    float bm = bernstein(m, 3, u);
//                    float bn = bernstein(n, 3, v);
//                    point.addX(controlPoints[m * 4 + n].getX() * bm * bn);
//                    point.addY(controlPoints[m * 4 + n].getY() * bm * bn);
//                    point.addZ(controlPoints[m * 4 + n].getZ() * bm * bn);
//                }
//            }
//            // res.push_back(point);
//            //crt.at(v) = point;
//             points[i][j] = point;
//        }
//        //points.at(u) = crt;
//    }
//
//     for(i = 0; i < level; ++i) {
//         for(j = 0; j < level; ++j) {
//             res.push_back(points[i][j+1]);
//             res.push_back(points[i+1][j]);
//             res.push_back(points[i][j]);
//
//             res.push_back(points[i+1][j]);
//             res.push_back(points[i][j+1]);
//             res.push_back(points[i+1][j+1]);
//         }
//     }
//
//    return res;
    // vector<Point> points;
    // vector<Point> controlPoints = getPoints();
    // int n = controlPoints.size();
    // float step = 1.0f / level;
    // for(float t = .01f; t <= 1.0f; t += step) {
    //     Point point;
    //     for(int i = 0; i < n; i++) {
    //         float b = binomial(n, i);
    //         float x = pow(1 - t, n - i) * pow(t, i) * controlPoints[i].getX();
    //         float y = pow(1 - t, n - i) * pow(t, i) * controlPoints[i].getY();
    //         float z = pow(1 - t, n - i) * pow(t, i) * controlPoints[i].getZ();
    //         point.setX(point.getX() + b * x);
    //         point.setY(point.getY() + b * y);
    //         point.setZ(point.getZ() + b * z);
    //     }
    //     points.push_back(point);
    // }
//}

// vector<vector<int>> Patch::tessellate(int level) {
//     vector<vector<int>> triangles;
//     int i, j, k, l;

//     for(i = 0; i < level; ++i) {
//         vector<vector<int>> newTriangles;
//         for(j = 0; j < triangles.size(); ++j) {
//             vector<int> triangle = triangles[j];
//             for(k = 0; k < 3; ++k) {
//                 Point p1 = controlPoints[triangle[k]];
//                 Point p2 = controlPoints[triangle[(k+1)%3]];
//                 Point p3 = controlPoints[triangle[(k+2)%3]];

//                 Point p4 = Point(p1.getX() + (p2.getX() - p1.getX())/3, p1.getY() + (p2.getY() - p1.getY())/3, p1.getZ() + (p2.getZ() - p1.getZ())/3);
//                 Point p5 = Point(p2.getX() + (p3.getX() - p2.getX())/3, p2.getY() + (p3.getY() - p2.getY())/3, p2.getZ() + (p3.getZ() - p2.getZ())/3);
//                 Point p6 = Point(p4.getX() + (p5.getX() - p4.getX())/3, p4.getY() + (p5.getY() - p4.getY())/3, p4.getZ() + (p5.getZ() - p4.getZ())/3);

//                 int p7 = controlPoints.size();
//                 controlPoints.push_back(p4);
//                 int p8 = controlPoints.size();
//                 controlPoints.push_back(p5);
//                 int p9 = controlPoints.size();
//                 controlPoints.push_back(p6);

//                 vector<int> triangle1 = {triangle[k], p7, p9};
//                 vector<int> triangle2 = {p7, triangle[(k+1)%3], p8};
//                 vector<int> triangle3 = {p9, p8, triangle[(k+2)%3]};
//                 vector<int> triangle4 = {p7, p8, p9};

//                 newTriangles.push_back(triangle1);
//                 newTriangles.push_back(triangle2);
//                 newTriangles.push_back(triangle3);
//                 newTriangles.push_back(triangle4);
//             }
//         }
//         triangles = newTriangles;
//     }

//     return triangles;
// }