#include "main.h"

void plane(float units, int divisions, string filename){
    Model model;   
    float x, y, z, div;
    y = 0;
    z = x = units / 2;
    div = units / divisions;
    
    for(float i = -x; i < x ; i+=div){
        for(float j = -z; j < z; j+=div){
            Patch * patch;
            patch->addPoint(*(new Point(i, y, j)));
            patch->addPoint(*(new Point(i, y, j + div)));
            patch->addPoint(*(new Point(i + div, y, j + div)));

            patch->addPoint(*(new Point(i+ div, y, j+div)));
            patch->addPoint(*(new Point(i + div, y, j)));
            patch->addPoint(*(new Point(i, y, j)));

            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void box(float units, int grid, string filename){
    cout << "Units: " << units << ", Grid: " << grid << ", Filename: " << filename << endl;
}

void cone(float radius, float height, int slices, int stacks, string filename){
    cout << "Radius: " << radius << ", Height: " << height << ", Slices: " << slices << ", Stacks: " << stacks << ", Filename: " << filename << endl;
}

void sphere(float radius, int slices, int stacks, string filename){
    cout << "Radius: " << radius << ", Slices: " << slices << ", Stacks: " << stacks << ", Filename: " << filename << endl;
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
