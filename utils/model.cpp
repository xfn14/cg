#include "model.h"

int Model::getVbo() {
    return Model::vboId;
}

void Model::addPatch(Patch  patch) {
    Model::patches.push_back(patch);
}

vector<Patch > Model::getPatches() {
    return Model::patches;
}

void Model::readModelPatch(string path) {
    ifstream file(path);

    string np;
    std::getline(file, np);
    int n = stoi(np);

    Patch patch;
    for(int i = 0; i < n; i++) {
        string line;
        std::getline(file, line);
        float x, y, z;
        sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
        if(x != 0 && y != 0 && z != 0)
            patch.addPoint(Point(x, y, z));
    }
    addPatch(patch);
}

void Model::writeToFile(string path) {
    ofstream file(path);

    file << patches.size() << endl;

    // TODO Aproveitar pontos repetidos para o indices dos pontos
    // Maybe meter os pontos num mapa antes de os escrever para reduzir repetidos

    int i, j, pointIndex = 0;
    for(Patch  patch : patches){
        for(j = 0; j < patch.getPoints().size(); ++j)
            file << pointIndex++ << " ";
        file << endl;
    }

    file << pointIndex << endl;
    for(Patch  patch : patches){
        vector<Point> controlPoints = patch.getPoints();
        vector<Point> normals = patch.getNormals();
        vector<Point> textures = patch.getTexture();
        for(j = 0; j < controlPoints.size(); ++j)
            file << " " << controlPoints[j].getX() << ", " << controlPoints[j].getY() << ", " << controlPoints[j].getZ()
                 << " " << normals[j].getX() << " " << normals[j].getY() << " " << normals[j].getZ()
                 << " " << textures[j].getX() << " " << textures[j].getY() << endl;
    }

    file.close();
}

int Model::readModel(string path) {
    std::ifstream file(path);
    
    if(!file.is_open()) return 0;

    // Load Patches indexes
    string np;
    std::getline(file, np);
    int numPatch = stoi(np), i, j;
    vector<vector<int>> patchesIndexes;
    for(i = 0; i < numPatch; ++i) {
        string line, temp = "";
        std::getline(file, line);
        vector<int> indexes;
        for(j = 0; j < line.length(); ++j) {
            if(line[j] == ',' || line[j] == '\n' || line[j] == '\r') continue;
            else if(line[j] == ' ' && temp != "") {
                indexes.push_back(stoi(temp));
                temp = "";
            } else temp.push_back(line[j]);
        }
        if(temp != "" && temp != " ") indexes.push_back(stoi(temp));
        
        patchesIndexes.push_back(indexes);
    }

    // Load control points
    std::getline(file, np);
    int numPoints = stoi(np), crt = 0;
    Point points[numPoints];
    Point normals[numPoints];
    Point textures[numPoints];
    for(i = 0; i < numPoints; ++i) {
        string line;
        std::getline(file, line);
        float x, y, z, nx, ny, nz, tx, ty;
        sscanf(line.c_str(), " %f, %f, %f, %f, %f, %f, %f, %f", &x, &y, &z, &nx, &ny, &nz, &tx, &ty);
        points[i] = Point(x, y, z);
        normals[i] = Point(nx, ny, nz);
        textures[i] = Point(tx, ty, 0);
    }

    // Merge loaded patches indexes with loaded control points
    for(vector<int> crtPatch : patchesIndexes) {
        Patch * patch = new Patch();
        for(int idx : crtPatch) {
            patch->addPoint(points[idx]);
            patch->addNormals(normals[idx]);
            patch->addTexture(textures[idx]);
        }
        addPatch(*patch);
    }
    return 1;
}

void Model::tessellate(int level, string path) {
    Model model;
    vector<Point> points;
    for (Patch patch: patches) {
        Patch newPatch;
        vector<Point> res = patch.tessellate(level);
        int i = 0;
        for (Point point: res) {
            cout << point.getX() << " " << point.getY() << " " << point.getZ() << endl;
            points.push_back(point);
            newPatch.addPoint(point);
            newPatch.addNormals(patch.getNormals()[i]);
            i++;
        }
        model.addPatch(newPatch);
    }
    model.writeToFile("bezier.3d");
}

void Model::loadTexture(string path) {
    // TODO
}