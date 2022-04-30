#include "model.h"

void Model::addPatch(Patch  patch) {
    patches.push_back(patch);
}

vector<Patch > Model::getPatches() {
    return patches;
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

// Tessellate the bezier surface that contains a vector of patch into triangles and output them to a file
// with each line containing the indexes of the 3 points of the triangle
void Model::tessellate(int level, string path) {
    vector<Point> points;

    int i;
    for(i = 0; i < patches.size(); ++i) {
        vector<Point> crtTriangles = patches[i].tessellate(level);
        for(Point triangle : crtTriangles)
            points.push_back(triangle);
    }
    ofstream file(path + ".model");
    file << points.size() << endl;
    for(Point point : points){
        file << point.getX() << " " << point.getY() << " " << point.getZ() << endl;
    }
    file.close();
}

    // vector<Patch> patches = getPatches();
    // vector<Point> points;
    // vector<vector<int>> triangles;

    // for(Patch patch : patches) {
    //     vector<Point> controlPoints = patch.getPoints();
    //     for(int i = 0; i < controlPoints.size(); ++i) points.push_back(controlPoints[i]);
    // }

    // int i, j, k, l;

    // for(i = 0; i < level; ++i) {
    //     vector<vector<int>> newTriangles;
    //     for(j = 0; j < triangles.size(); ++j) {
    //         vector<int> triangle = triangles[j];
    //         for(k = 0; k < 3; ++k) {
    //             Point p1 = points[triangle[k]];
    //             Point p2 = points[triangle[(k+1)%3]];
    //             Point p3 = points[triangle[(k+2)%3]];

    //             Point p4 = Point(p1.getX() + (p2.getX() - p1.getX())/3, p1.getY() + (p2.getY() - p1.getY())/3, p1.getZ() + (p2.getZ() - p1.getZ())/3);
    //             Point p5 = Point(p2.getX() + (p3.getX() - p2.getX())/3, p2.getY() + (p3.getY() - p2.getY())/3, p2.getZ() + (p3.getZ() - p2.getZ())/3);
    //             Point p6 = Point(p4.getX() + (p5.getX() - p4.getX())/3, p4.getY() + (p5.getY() - p4.getY())/3, p4.getZ() + (p5.getZ() - p4.getZ())/3);

    //             int p7 = points.size();
    //             points.push_back(p4);
    //             int p8 = points.size();
    //             points.push_back(p5);
    //             int p9 = points.size();
    //             points.push_back(p6);
    //         }

    // if(level == 0) {
    //     Patch patch;
    //     for(int i = 0; i < indexes.size(); ++i)
    //         patch.addPoint(patches[0].getPoints()[indexes[i]]);
    //     addPatch(patch);
    // } else {
    //     for(int i = 0; i < indexes.size(); ++i) {
    //         vector<Point> points = patches[0].getPoints();
    //         vector<int> newIndexes = indexes;
    //         newIndexes.erase(newIndexes.begin()+i);
    //         tessellate(level-1, newIndexes);
    //         for(int j = 0; j < indexes.size(); ++j) {
    //             if(j == i) continue;
    //             Patch patch;
    //             Point p1 = points[indexes[i]], p2 = points[indexes[j]];
    //             Point p3 = Point(p1.getX() + (p2.getX()-p1.getX())/2, p1.getY() + (p2.getY()-p1.getY())/2, p1.getZ() + (p2.getZ()-p1.getZ())/2);
    //             patch.addPoint(p1);
    //             patch.addPoint(p2);
    //             patch.addPoint(p3);
    //             addPatch(patch);
    //         }
    //     }
    // }