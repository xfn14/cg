#include "model.h"

void Model::addPatch(Patch patch) {
    patches.push_back(patch);
}

vector<Patch> Model::getPatches() {
    return patches;
}

void Model::writeToFile(string path) {
    ofstream file(path);

    file << patches.size() << endl;

    // TODO Aproveitar pontos repetidos para o indices dos pontos
    // Maybe meter os pontos num mapa antes de os escrever para reduzir repetidos

    int i, j, pointIndex = 0;
    for(i = 0; i < patches.size(); ++i) {
        Patch patch = patches[i];
        for(j = 0; j < patch.getPoints().size(); ++j)
            file << pointIndex++ << " ";
        file << endl;
    }

    for(i = 0; i < patches.size(); ++i) {
        vector<Point> controlPoints = patches[i].getPoints();
        for(j = 0; j < controlPoints.size(); ++j)
            file << controlPoints[j].getX() << " " << controlPoints[j].getY() << " " << controlPoints[j].getZ() << endl;
    }

    file.close();
}