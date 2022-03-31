#ifndef _WORLD_
#define _WORLD_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include <math.h>

#include "camera.h"
#include "../utils/model.h"
#include "../libs/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Group {
    private:
        vector<Model> models;
        vector<Group> subGroups;

    public:
        void addModel(Model model);
        vector<Model> getModels();
        void addGroup(Group group);
        vector<Group> getGroups();
        void translate(float x, float y, float z);
        void rotate(float angle, float x, float y, float z);
        void scale(float x, float y, float z);
};

class World {
    private:
        Camera camera;
        Group group;

    public:
        Camera getCamera();
        Group getGroup();
        void addModel(Model model);
        int parseXML(string path, string filename);
        void parseCamera(XMLElement * elem);
        void parseGroup(string path, XMLElement * elem, Group group);
        void parseModels(string path, XMLElement * elem, Group group);
        void parseTransform(XMLElement * elem, Group group);
};

#endif