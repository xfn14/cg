#include "main.h"

void plane(float units, int divisions, string filename){

    float x, y, z, xs, zs, div;
    y = 0;
    vector<Point*> vertices;

    x = units/2;
    y = units/2;
    div = units/divisions;
    xs = x-div;
    zs = z-div;

    for(int i = 0;;)

    vertices.push_back(new Point(-x,y,-z));
    vertices.push_back(new Point(-x,y,-zs));
    vertices.push_back(new Point(-xs,y,-zs));

    vertices.push_back(new Point(-xs,y,-zs));
    vertices.push_back(new Point(-xs,y,-z));
    vertices.push_back(new Point(-x,y,-z));

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
