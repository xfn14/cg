#ifndef _MODEL_
#define _MODEL_

#include <fstream>

#include "patch.h"

using namespace std;

class Model {
    private:
    vector<Patch> patches;

    public:
        void addPatch(Patch);
        vector<Patch> getPatches();
        void writeToFile(string path);
};

#endif