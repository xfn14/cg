#include "world.h"

Camera World::getCamera() {
    return camera;
}

vector<Model> World::getModels() {
    return models;
}

void World::addModel(Model model) {
    models.push_back(model);
}

int World::parseXML(string path, string filename) {
    string file = path + filename;
    cout << "Loading " << file << "." << endl;
    XMLDocument doc;
    if(!doc.LoadFile(file.c_str())){
        XMLElement * cameraElem = doc.FirstChildElement("world")->FirstChildElement("camera");
        XMLElement * groupElem = doc.FirstChildElement("world")->FirstChildElement("group");
        
        World::parseCamera(cameraElem);
        World::parseGroup(path, groupElem);

        cout << "Finished loading " << file << "." << endl;
        return 1;
    }
    cout << "Failed to load " << file << "." << endl;
    return 0;
}

void World::parseCamera(XMLElement * elem) {
    float posX, posY, posZ;
    XMLElement * positionElem = elem->FirstChildElement("position");
    positionElem->QueryFloatAttribute("x", &posX);
    positionElem->QueryFloatAttribute("y", &posY);
    positionElem->QueryFloatAttribute("z", &posZ);
    World::camera.setPosition(new Point(posX, posY, posZ));

    float lookAtX, lookAtY, lookAtZ;
    XMLElement * lookAtElem = elem->FirstChildElement("lookAt");
    lookAtElem->QueryFloatAttribute("x", &lookAtX);
    lookAtElem->QueryFloatAttribute("y", &lookAtY);
    lookAtElem->QueryFloatAttribute("z", &lookAtZ);
    World::camera.setLookAt(new Point(lookAtX, lookAtY, lookAtZ));

    float upX, upY, upZ;
    XMLElement * upElem = elem->FirstChildElement("up");
    upElem->QueryFloatAttribute("x", &upX);
    upElem->QueryFloatAttribute("y", &upY);
    upElem->QueryFloatAttribute("z", &upZ);
    World::camera.setUp(new Point(upX, upY, upZ));

    int fov, near, far;
    XMLElement * projectionElem = elem->FirstChildElement("projection");
    projectionElem->QueryIntAttribute("x", &fov);
    projectionElem->QueryIntAttribute("y", &near);
    projectionElem->QueryIntAttribute("z", &far);
    World::camera.setFov(fov);
    World::camera.setNear(near);
    World::camera.setFar(far);
}

void World::parseGroup(string path, XMLElement * elem) {
    for(XMLElement * child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
        string val = child->Value();
        if(val == "models") {
            parseModels(path, child);
        } else if(child->Value() == "group")
            parseGroup(path, child);
    }
}

void World::parseModels(string path, XMLElement * elem) {
    for(XMLElement * child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
        string val = child->Value();
        if(val == "model") {
            string filename = child->Attribute("file");
            Model model;
            cout << path << filename << endl;
            model.readModel(path + filename);
            World::addModel(model);
        }
    }
}

void Model::drawModel() {
    /*for(Patch patch : getPatches()) {
        vector<Point> points = patch.getPoints();
        for(int i=0; i<points.size()/3; i++) {
            Point point1 = points[i*3];
            Point point2 = points[i*3+1];
            Point point3 = points[i*3+2];
            glBegin(GL_TRIANGLES);
            glVertex3f(point1.getX(), point1.getY(), point1.getZ());
            glVertex3f(point2.getX(), point2.getY(), point2.getZ());
            glVertex3f(point3.getX(), point3.getY(), point3.getZ());
            glEnd();
        }

    }*/
    for(Patch patch : getPatches()) {
        glBegin(GL_TRIANGLES);
        vector<Point> primitives = patch.getPoints();
        for (int i = 0; i < primitives.size(); i++){


                glColor3f(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                          static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                          static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

                Point point = primitives[i];

                glVertex3f(point.getX(), point.getY(), point.getZ());

    } glEnd();
}


}
