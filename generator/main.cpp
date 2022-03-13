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
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) (i+1)*div, z)));

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) i*div, z)));

            model.addPatch(patch);

        }
    }
    model.writeToFile(filename);

}

void cone(float radius, float height, int slices, int stacks, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices), deltav = height/(float) stacks, deltaRaio = radius/(float) stacks;
    float y=height/2;
    float  alturaS,alturaS2;

    for(int j=0; j<stacks; j++){
        for(int i=0; i<slices; i++){
            float angle1 = (float) i * deltah, angle2 = (float) (i + 1) * deltah;
            Patch patch;
            if(j == 0) {
                //base
                patch.addPoint(*(new Point(0.0f, -y, 0.0f)));
                patch.addPoint(*(new Point(radius * sinf(angle2), -y, radius * cosf(angle2))));
                patch.addPoint(*(new Point(radius * sinf(angle1), -y, radius * cosf(angle1))));
            }
            //laterais
            float raioStack1 = radius - (float) j * deltaRaio;
            float raioStack2 = radius - (float) (j+1) * deltaRaio;
            alturaS = -y + (float) j * deltav;
            alturaS2 = -y + (float) (j+1) * deltav;
            if (j < stacks-1) {
                patch.addPoint(*(new Point(raioStack1 * sinf(angle1), alturaS, raioStack1 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS2, raioStack2 * cosf(angle1))));

                patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS+deltav, raioStack2 * cosf(angle1))));
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

void torus(float radius, float radiusS,float radiusB, int slices, int stacks, string filename){

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
    }  else if (argc == 8 && strcmp(argv[1], "torus") == 0) {
        torus(
                atof(argv[2]),
                atof(argv[3]),
                atof(argv[4]),
                atoi(argv[5]),
                atoi(argv[6]),
                argv[7]
        );
        return 0;
    }
    return 0;
}
