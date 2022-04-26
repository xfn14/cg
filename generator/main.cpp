#include "main.h"

void plane(float units, int divisions, string filename){
    Model model;   
    float x, z, div;
    z = x = -(units/2);
    div = units / (float) divisions;

    for (int i=0; i<divisions; i++){
        for(int j=0; j<divisions; j++){
            Patch patch;

            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) i*div)));

            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) (i+1)*div)));

            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void box(float units, int grid, string filename){
    Model model;
    float x, y, z, div;
    x = y = z = - units/2;
    div = units/(float) grid;

    for (int i=0; i < grid; i++){
        for(int j=0; j < grid; j++){
            Patch patch;
            //face de cima
            patch.addPoint(*(new Point(x + (float) (j+1)*div, -y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) j*div, -y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, -y, z + (float) (i+1)*div)));

            patch.addPoint(*(new Point(x + (float) (j+1)*div, -y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, -y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, -y, z + (float) i*div)));

            //face de baixo
            patch.addPoint(*(new Point(x + (float) j*div, y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) j*div, y, z + (float) (i+1)*div)));

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) j*div, y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y, z + (float) i*div)));

            //face lateral -x
            patch.addPoint(*(new Point(x , y + (float) i*div, z + (float) j*div)));
            patch.addPoint(*(new Point(x , y + (float) (i+1)*div, z + (float) (j+1)*div)));
            patch.addPoint(*(new Point(x , y + (float) (i+1)*div, z + (float) j*div)));

            patch.addPoint(*(new Point(x , y + (float) (i+1)*div, z + (float) (j+1)*div)));
            patch.addPoint(*(new Point(x , y + (float) i*div, z + (float) j*div)));
            patch.addPoint(*(new Point(x , y + (float) i*div, z + (float) (j+1)*div)));

            //face lateral x
            patch.addPoint(*(new Point(-x, y + (float) i*div, z + (float) j*div )));
            patch.addPoint(*(new Point(-x, y + (float) (i+1)*div, z + (float) j*div)));
            patch.addPoint(*(new Point(-x, y + (float) (i+1)*div, z + (float) (j+1)*div)));

            patch.addPoint(*(new Point(-x, y + (float) (i+1)*div, z + (float) (j+1)*div)));
            patch.addPoint(*(new Point(-x, y + (float) i*div, z + (float) (j+1)*div)));
            patch.addPoint(*(new Point(-x, y + (float) i*div, z + (float) j*div)));

            //face lateral z
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, -z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, -z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) i*div, -z)));

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, -z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) (i+1)*div, -z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, -z)));

            //face lateral -z
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) (i+1)*div, z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, z)));

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) i*div, z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, z)));

            model.addPatch(patch);

        }
    }
    model.writeToFile(filename);

}

void cone(float radius, float height, int slices, int stacks, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices), deltav = height/(float) stacks, deltaRaio = radius/(float) stacks;
    float y=height;
    float  alturaS,alturaS2;

    for(int j=0; j<stacks; j++){
        for(int i=0; i<slices; i++){
            float angle1 = (float) i * deltah, angle2 = (float) (i + 1) * deltah;
            Patch patch;
            if(j == 0) {
                //base
                patch.addPoint(*(new Point(0.0f, 0.0f, 0.0f)));
                patch.addPoint(*(new Point(radius * sinf(angle2), 0.0f, radius * cosf(angle2))));
                patch.addPoint(*(new Point(radius * sinf(angle1), 0.0f, radius * cosf(angle1))));
            }
            //laterais
            float raioStack1 = radius - (float) j * deltaRaio;
            float raioStack2 = radius - (float) (j+1) * deltaRaio;
            alturaS = (float) j * deltav;
            alturaS2 =  (float) (j+1) * deltav;
            if (j < stacks-1) {
                patch.addPoint(*(new Point(raioStack1 * sinf(angle1), alturaS, raioStack1 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS2, raioStack2 * cosf(angle1))));

                patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS2, raioStack2 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(raioStack2 * sinf(angle2), alturaS2, raioStack2 * cosf(angle2))));
            }
            else{
                patch.addPoint(*(new Point(raioStack1 * sinf(angle1), alturaS, raioStack1 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(0, y, 0)));
            }
            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void sphere(float radius, int slices, int stacks, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices), deltav = (float)M_PI/(float) stacks;
    for(int i=0; i<slices; i++){
        for(int j=0; j<stacks; j++) {
            float beta1 = (float) i * deltah, beta2 = (float) (i + 1) * deltah;
            float theta1 = (float) j * deltav, theta2 = (float) (j + 1) * deltav;
            Patch patch;
            if (j == 0) {
                //triangulo de cima
                patch.addPoint(*(new Point(0, radius, 0)));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta1),radius*cosf(theta2),radius*sinf(theta2)*cosf(beta1))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta2),radius*cosf(theta2),radius*sinf(theta2)*cosf(beta2))));
            } else if (j == stacks - 1) {
                //triangulo de baixo
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta2), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta2))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta1), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta1))));
                patch.addPoint(*(new Point(0, -radius, 0)));
            } else{
                patch.addPoint(*(new Point(radius*sinf(theta1)*sinf(beta1), radius*cosf(theta1), radius*sinf(theta1)*cosf(beta1))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta1), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta1))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta2), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta2))));

                patch.addPoint(*(new Point(radius*sinf(theta1)*sinf(beta2), radius*cosf(theta1), radius*sinf(theta1)*cosf(beta2))));
                patch.addPoint(*(new Point(radius*sinf(theta1)*sinf(beta1), radius*cosf(theta1), radius*sinf(theta1)*cosf(beta1))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta2), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta2))));
            }
            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void tronco(float radius1, float radius2, float height, int slices, int stacks, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices), deltav = height/(float) stacks, deltaRaio = abs(radius1-radius2)/(float) stacks;
    float y=height/2;
    float  alturaS,alturaS2;

    for(int j=0; j<stacks; j++){
        for(int i=0; i<slices; i++){
            float angle1 = (float) i * deltah, angle2 = (float) (i + 1) * deltah;
            Patch patch;
            if(j == 0) {
                //base
                patch.addPoint(*(new Point(0.0f, -y, 0.0f)));
                patch.addPoint(*(new Point(radius2 * sinf(angle2), -y, radius2 * cosf(angle2))));
                patch.addPoint(*(new Point(radius2 * sinf(angle1), -y, radius2 * cosf(angle1))));
            }
            //laterais
            float raioStack1 = radius2 - (float) j * deltaRaio;
            float raioStack2 = radius2 - (float) (j+1) * deltaRaio;
            if(radius1>radius2){
                raioStack1 = radius2 + (float) j * deltaRaio;
                raioStack2 = radius2 + (float) (j+1) * deltaRaio;
            }
            alturaS = -y + (float) j * deltav;
            alturaS2 = -y + (float) (j+1) * deltav;
            if (j == stacks-1) {
                patch.addPoint(*(new Point(0.0f, y, 0.0f)));
                patch.addPoint(*(new Point(radius1 * sinf(angle1), y, radius1 * cosf(angle1))));
                patch.addPoint(*(new Point(radius1 * sinf(angle2), y, radius1 * cosf(angle2))));
            }

                patch.addPoint(*(new Point(raioStack1 * sinf(angle1), alturaS, raioStack1 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS2, raioStack2 * cosf(angle1))));

                patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS + deltav, raioStack2 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(raioStack2 * sinf(angle2),alturaS2, raioStack2 * cosf(angle2))));

            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void anel(float radius1, float radius2, int slices, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices);
    float y=0;

    if (radius1 < radius2){
        float temp = radius2;
        radius2 = radius1;
        radius1 = temp;
    }

    for(int i=0; i<slices; i++) {
        float angle1 = (float) i * deltah, angle2 = (float) (i + 1) * deltah;
        Patch patch;

        patch.addPoint(*(new Point(radius2 * sinf(angle1), y, radius2 * cosf(angle1))));
        patch.addPoint(*(new Point(radius1 * sinf(angle2), y, radius1 * cosf(angle2))));
        patch.addPoint(*(new Point(radius2 * sinf(angle2), y, radius2 * cosf(angle2))));

        patch.addPoint(*(new Point(radius2 * sinf(angle1), y, radius2 * cosf(angle1))));
        patch.addPoint(*(new Point(radius1 * sinf(angle1), y, radius1 * cosf(angle1))));
        patch.addPoint(*(new Point(radius1 * sinf(angle2), y, radius1 * cosf(angle2))));

        model.addPatch(patch);
    }
    model.writeToFile(filename);
}

int main(int argc, char const *argv[]) {
    if (argc == 5 && strcmp(argv[1], "plane") == 0) {
        plane(
            atof(argv[2]),
            atoi(argv[3]),
            argv[4]
        );
        return 0;
    } else if (argc == 5 && strcmp(argv[1], "box") == 0) {
        box(
            atof(argv[2]),
            atoi(argv[3]),
            argv[4]
        );
        return 0;
    } else if (argc == 7 && strcmp(argv[1], "cone") == 0) {
        cone(
            atof(argv[2]),
            atof(argv[3]),
            atoi(argv[4]),
            atoi(argv[5]),
            argv[6]
        );
        return 0;
    } else if (argc == 6 && strcmp(argv[1], "sphere") == 0) {
        sphere(
            atof(argv[2]),
            atoi(argv[3]),
            atoi(argv[4]),
            argv[5]
        );
        return 0;
    }  else if (argc == 8 && strcmp(argv[1], "tronco") == 0) {
        tronco(
                atof(argv[2]),
                atof(argv[3]),
                atof(argv[4]),
                atoi(argv[5]),
                atoi(argv[6]),
                argv[7]
        );
        return 0;
    } else if (argc == 6 && strcmp(argv[1], "anel") == 0) {
        anel(
                atof(argv[2]),
                atof(argv[3]),
                atoi(argv[4]),
                argv[5]
        );
        return 0;

    }
    return 0;
}

// Read bezier surface from text file which contains the description of a set of Bezier patches. The first line contains the number
// of patches. The following lines, one for each patch, contain the indices of the control points (16 for
// each patch). The next line contains the number of control points, and afterwards the control points
// themselves, one per line.
//
// The format of the file is:
//
// n
// i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16
// i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16
// ...
// n
// x, y, z
// x, y, z
// ...
//
// where n is the number of patches, i1, i2, ..., i16 are the indices of the 16 control points of the patch, and
// x, y, z are the coordinates of the control point.
//
// The function returns a pointer to a Model object.
// Model *readModel(const char *filename) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cerr << "Error: could not open file " << filename << endl;
//         exit(1);
//     }

//     int nPatches;
//     file >> nPatches;
//     Model *model = new Model();
//     for (int i = 0; i < nPatches; i++) {
//         Patch patch;
//         for (int j = 0; j < 16; j++) {
//             int index;
//             file >> index;
//             patch.addPoint(*(new Point(model->getControlPoint(index))));
//         }
//         model->addPatch(patch);
//     }

//     int nControlPoints;
//     file >> nControlPoints;
//     for (int i = 0; i < nControlPoints; i++) {
//         float x, y, z;
//         file >> x >> y >> z;
//         model->addControlPoint(*(new Point(x, y, z)));
//     }

//     return model;
// }

