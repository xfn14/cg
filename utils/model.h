#ifndef _MODEL_
#define _MODEL_

#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "patch.h"
#include "../engine/transforms.h"
#include "../utils/matrix.h"

using namespace std;

class Model {
    private:
        int vbo = 0;
        GLuint vboId;
        vector<Patch> patches;

    public:
        Model(){
        }

        Model(string path) {
            Model::readModel(path);
        }
        
        int getVbo();
        void initVbo();
        void addPatch(Patch patch);
        vector<Patch> getPatches();
        void readModelPatch(string path);
        void writeToFile(string path);
        int readModel(string path);
        void drawModel(Color color);
        void tessellate(int level, string path);
};

#endif