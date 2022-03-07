#ifndef _WORLD_
#define _WORLD_

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
        int parseXML(string path);
        void parseCamera(XMLElement * elem);
        void parseGroup(XMLElement * elem);
};

#endif