#ifndef _MATRIX_
#define _MATRIX_

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "../utils/point.h"

using namespace std;

void buildRotMatrix(float *x, float *y, float *z, float *m);
void toVector(float *a,float *b, float *res);
void cross(float *a, float *b, float *res);
void normalize(float *a);
float length(float *v);
void multMatrixVector(float *m, float *v, float *res);

#endif