#include "main.h"


void plane(float units, int divisions, string filename){
    Model model;   
    float x, z, div;
    z = x = -(units/2);
    div = units / (float) divisions;
    /*
    for(float i = -x; i < x ; i+=div){
        for(float j = -z; j < z; j+=div){
            Patch patch;
            patch.addPoint(*(new Point(i, 0, j)));
            patch.addPoint(*(new Point(i, 0, j + div)));
            patch.addPoint(*(new Point(i + div, 0, j + div)));

            patch.addPoint(*(new Point(i+ div, 0, j+div)));
            patch.addPoint(*(new Point(i, 0, j)));
            patch.addPoint(*(new Point(i + div, 0, j)));

            model.addPatch(&patch);
        }
    }*/
    for (int i=0; i<divisions; i++){
        for(int j=0; j<divisions; j++){
            Patch patch;
            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) (i+1)*div)));


            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) i*div)));

            model.addPatch(&patch);
            model.writeToFile(filename);
        }
    }
}

void box(float units, int grid, string filename){
    Model model;
    float x, y, z, div;
    x = y = z = - units/2;
    div = units/(float) grid;
    /*
    //Fundo do Cubo
    for(int j = -x; j < x; j+=div){
        for(int k = -z; k < z; k+=div){
            Patch* patch;
            patch.addPoint(*(new Point(j, -y, k)));
            patch.addPoint(*(new Point(j, -y, k+div)));
            patch.addPoint(*(new Point(j+div, -y, k+div)));

            patch.addPoint(*(new Point(j+div, -y, k+div)));
            patch.addPoint(*(new Point(j+div, -y, k)));
            patch.addPoint(*(new Point(j, -y, k)));

            model.addPatch(patch);
        }
    }

    //Topo do Cubo
    for(int j = -x; j < x; j+=div){
        for(int k = -z; k < z; k+=div){
            Patch* patch;
            patch.addPoint(*(new Point(j, y, k)));
            patch.addPoint(*(new Point(j, y, k+div)));
            patch.addPoint(*(new Point(j+div, y, k+div)));

            patch.addPoint(*(new Point(j+div, y, k+div)));
            patch.addPoint(*(new Point(j+div, y, k)));
            patch.addPoint(*(new Point(j, y, k)));

            model.addPatch(patch);
        }
    }

    //Lateral do Cubo
    for(int i = -y; i < y; i+=div){
        for(int j = -x; j < x; j+=div){
            Patch* patch;
            for(int k = -z; k < z; k+=div){
                patch.addPoint(*(new Point(j, i+div, k)));
                patch.addPoint(*(new Point(j+div, i+div, k)));
                patch.addPoint(*(new Point(j+div, i, k)));

                patch.addPoint(*(new Point(j+div, i, k)));
                patch.addPoint(*(new Point(j, i, k)));
                patch.addPoint(*(new Point(j, i+div, k)));
            }


            patch.addPoint(*(new Point(-x, i+div, (-z) + div)));
            patch.addPoint(*(new Point(-x, i+div, -z)));
            patch.addPoint(*(new Point(-x, i, -z)));

            patch.addPoint(*(new Point(-x, i, -z)));
            patch.addPoint(*(new Point(-x, i, (-z) + div)));
            patch.addPoint(*(new Point(-x, i+div, (-z) + div)));

            
        }
    }
             */

    for (int i=0; i < grid; i++){
        for(int j=0; j < grid; j++){
            Patch patch;
            //face de cima
            patch.addPoint(*(new Point(x + (float) j*div, -y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, -y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, -y, z + (float) (i+1)*div)));

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
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, -z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) (i+1)*div, -z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, -z)));

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, -z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) i*div, -z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, -z)));

            //face lateral -z
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) (i+1)*div, z)));

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) i*div, z)));

            model.addPatch(&patch);
            model.writeToFile(filename);
        }
    }


}

void cone(float radius, float height, int slices, int stacks, string filename){
    cout << "Radius: " << radius << ", Height: " << height << ", Slices: " << slices << ", Stacks: " << stacks << ", Filename: " << filename << endl;

    Model model;
    float deltah = (2*(float)M_PI/(float)slices), deltav = height/stacks, deltaRaio = radius/stacks;
    float y=height/2;

    float raioStack, alturaS;

    for(int j=0; j<stacks; j++){
        for(int i=0; i<slices; i++){
            Patch patch;
            float angle1 = (float)i*deltah, angle2 = (float)(i+1)*deltah;
            //base
            patch.addPoint(*(new Point(0.0f,-y,0.0f)));
            patch.addPoint(*(new Point(radius*sinf(angle2),-y,radius*cosf(angle2))));
            patch.addPoint(*(new Point(radius*sinf(angle1),-y,radius*cosf(angle1))));

            //laterais
            raioStack = radius - (float) j*deltaRaio;
            alturaS = -y + (float) j*deltav;

            if (j == stacks-1){
                patch.addPoint(*(new Point(raioStack * sinf(angle1), alturaS, raioStack * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack * sinf(angle2), alturaS, raioStack * cosf(angle2))));
                patch.addPoint(*(new Point(0, height, 0)));
            }
            else {
                patch.addPoint(*(new Point(raioStack * sinf(angle1), alturaS, raioStack * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack * sinf(angle2), alturaS, raioStack * cosf(angle2))));
                patch.addPoint(*(new Point((raioStack + deltaRaio) * sinf(angle1), alturaS+deltav, (raioStack + deltaRaio) * cosf(angle1))));

                patch.addPoint(*(new Point((raioStack + deltaRaio) * sinf(angle1), alturaS+deltav, (raioStack + deltaRaio) * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack * sinf(angle2), alturaS, raioStack * cosf(angle2))));
                patch.addPoint(*(new Point((raioStack + deltaRaio) * sinf(angle2), alturaS+deltav, (raioStack + deltaRaio) * cosf(angle2))));

            }

            model.addPatch(&patch);
            model.writeToFile(filename);
        }
    }


}

void sphere(float radius, int slices, int stacks, string filename){
    cout << "Radius: " << radius << ", Slices: " << slices << ", Stacks: " << stacks << ", Filename: " << filename << endl;

    for(int i=0; i<slices; i++){

    }
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
    }
    return 0;
}
