#ifndef _WORLD_
#define _WORLD_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "camera.h"
#include "../utils/model.h"
#include "../libs/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class World {
    private:
        Camera camera;
        vector<Model> models;

    public:
        Camera getCamera();
        vector<Model> getModels();
        void addModel(Model model);
        int parseXML(string path, string filename);
        void parseCamera(XMLElement * elem);
        void parseGroup(string path, XMLElement * elem);
        void parseModels(string path, XMLElement * elem);
};

#endif