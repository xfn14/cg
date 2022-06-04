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
        float sizes[3];
        GLuint vboId, normalsId, textureId, texture;
        vector<Patch> patches;
        ModelColor color;
        string textura;

    public:
        Model(){
            textura = "";
        }

        Model(string path) {
            textura = "";
            Model::readModel(path);
        }

        Model(string path, string a) {
            textura = a;
            Model::readModel(path);
        }
        void setTextura(string textura){
            Model::textura=textura;
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
        void loadTexture(string path);
};

#endif