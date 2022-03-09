#include "model.h"

void Model::addPatch(Patch * patch) {
    patches.push_back(patch);
}

vector<Patch *> Model::getPatches() {
    return patches;
}

void Model::writeToFile(string path) {
    ofstream file(path);

    file << patches.size() << endl;

    // TODO Aproveitar pontos repetidos para o indices dos pontos
    // Maybe meter os pontos num mapa antes de os escrever para reduzir repetidos

    int i, j, pointIndex = 0;
    for(Patch * patch : patches){
        for(j = 0; j < patch->getPoints().size(); ++j)
            file << pointIndex++ << " ";
        file << endl;
    }

    for(Patch * patch : patches){
        vector<Point> controlPoints = patch->getPoints();
        for(j = 0; j < controlPoints.size(); ++j)
            file << controlPoints[j].getX() << " " << controlPoints[j].getY() << " " << controlPoints[j].getZ() << endl;
    }

    file.close();
}

int Model::readModel(string path) {
    std::ifstream file(path);
    if(!file.is_open()) return 0;

    // Load Patches indexes
    int numPatch;
    file >> numPatch;
    int i, j;
    vector<vector<int>> patchesIndexes;
    for(i = 0; i < numPatch; ++i) {
        string line, temp = "";
        std::getline(file, line);
        vector<int> indexes;
        for(j = 0; j < line.length(); ++j) {
            if(line[j] == ',' || line[j] == '\n') continue;
            else if(line[j] == ' ' && temp != "") {
                indexes.push_back(stoi(temp));
                temp = "";
            } else temp.push_back(line[j]);
        }
        if(temp != "") indexes.push_back(stoi(temp));
        patchesIndexes.push_back(indexes);
    }

    // Load control points
    int numPoints, crt = 0;
    file >> numPoints;
    Point points[numPoints];
    for(i = 0; i < numPoints; ++i) {
        string line, temp = "";
        std::getline(file, line);
        float x, y, z;
        int n = 0;
        for(j = 0; j < line.length(); ++j) {
            if(line[j] == ',' || line[j] == '\n') continue;
            else if(line[j] == '\n') {
                points[crt].setZ(stof(temp));
            } else if(line[j] == ' ' && temp != "") {
                if(n == 0) {
                    points[crt].setX(stof(temp));
                    n = 1;
                } else points[crt].setY(stof(temp));
                temp = "";
            } else temp.push_back(line[j]);
        }
        ++crt;
    }

    // Merge loaded patches indexes with loaded control points
    for(vector<int> crtPatch : patchesIndexes) {
        Patch * patch = new Patch();
        for(int idx : crtPatch)
            patch->addPoint(points[idx]);
        addPatch(patch);
    }
    return 1;
}