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
#include "transforms.h"
#include "../utils/model.h"
#include "../libs/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Group {
    private:
        vector<Model> models;
        vector<Translate> translates;
        vector<Rotate> rotates;
        vector<Scale> scales;
        Color color;
        vector<Group> subGroups;

    public:
        void addModel(Model model);
        vector<Model> getModels();
        void addTranslate(Translate translate);
        vector<Translate> getTranslate();
        void addRotate(Rotate rotate);
        vector<Rotate> getRotate();
        void addScale(Scale scale);
        vector<Scale> getScale();
        Color getColor();
        void setColor(Color c);
        void addGroup(Group group);
        vector<Group> getGroups();
        void translate(float x, float y, float z);
        void rotate(float angle, float x, float y, float z);
        void scale(float x, float y, float z);
};

class World {
    private:
        Camera camera;
        Group * group;

    public:
        Camera getCamera();
        Group* getGroup();
        void addModel(Model model);
        int parseXML(string path, string filename);
        void parseCamera(XMLElement * elem);
        void parseGroup(string path, XMLElement * elem, Group *g);
        void parseModels(string path, XMLElement * elem, Group *g);
        void parseTransform(XMLElement * elem, Group * g);
};

#endif