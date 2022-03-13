#include "model.h"

void Model::addPatch(Patch  patch) {
    patches.push_back(patch);
}

vector<Patch > Model::getPatches() {
    return patches;
}

void Model::writeToFile(string path) {
    ofstream file("../resources/tests/test2/" + path);

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
        for(j = 0; j < controlPoints.size(); ++j)
            file << controlPoints[j].getX() << " " << controlPoints[j].getY() << " " << controlPoints[j].getZ() << endl;
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
            if(line[j] == ',' || line[j] == '\n') continue;
            else if(line[j] == ' ' && temp != "") {
                indexes.push_back(stoi(temp));
                temp = "";
            } else temp.push_back(line[j]);
        }
        cout<<"f"<<temp<<"f"<<endl;
        if(temp != "" && temp != " ") indexes.push_back(stoi(temp));
        
        patchesIndexes.push_back(indexes);
    }

    // Load control points
    std::getline(file, np);
    int numPoints = stoi(np), crt = 0;
    Point points[numPoints];
    for(i = 0; i < numPoints; ++i) {
        string line, temp = "";
        std::getline(file, line);
        float x, y, z;
        int n = 0;
        
        for(j = 0; j < line.length()+1; ++j) {
            if(line[j] == ',') continue;
            else if(line[j] == ' ' && temp != "") {
                if(n == 0) {
                    points[crt].setX(stof(temp));
                    n = 1;
                } else points[crt].setY(stof(temp));
                temp = "";
            } else temp.push_back(line[j]);
        } if(temp != "") points[crt].setZ(stof(temp));
        ++crt;
    }

    // Merge loaded patches indexes with loaded control points
    for(vector<int> crtPatch : patchesIndexes) {
        Patch * patch = new Patch();
        for(int idx : crtPatch)
            patch->addPoint(points[idx]);
        addPatch(*patch);
    }
    return 1;
}