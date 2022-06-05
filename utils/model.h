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
#include "../engine/light.h"

using namespace std;

class Model {
    private:
        GLuint vboId, normalsId, textureId;
        vector<Patch> patches;
        ModelColor color;

    public:
        GLuint texture;

        Model(){
            texture = 0;
        }

        Model(string path) {
            texture = 0;
            Model::readModel(path);
        }
        
        ModelColor getColor();
        void setColor(ModelColor color);
        int getVbo();
        void initVbo();
        void addPatch(Patch patch);
        vector<Patch> getPatches();
        void readModelPatch(string path);
        void writeToFile(string path);
        int readModel(string path);
        void drawModel(Color color);
        void tessellate(int level, string path);
        int loadTexture(string path);
};

#endif