#ifndef _MODEL_
#define _MODEL_

#include <fstream>

#include "patch.h"
#include "../engine/transforms.h"

using namespace std;

class Model {
    private:
        vector<Patch> patches;

    public:
        Model(){}

        Model(string path) {
            Model::readModel(path);
        }

        void addPatch(Patch patch);
        vector<Patch> getPatches();
        void writeToFile(string path);
        int readModel(string path);
        void drawModel(Color color);
        void tessellate(int level, string path);
};

#endif