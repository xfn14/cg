#include "world.h"

void Group::addModel(Model model) {
    Group::models.push_back(model);
}

vector<Model> Group::getModels() {
    Group::models;
}

void Group::addGroup(Group group) {
    Group::subGroups.push_back(group);
}

vector<Group> Group::getGroups() {
    Group::subGroups;
}

void Group::translate(float x, float y, float z) {
    for(Model model : Group::models)
        for(Patch patch : model.getPatches())
            for(Point point : patch.getPoints()) {
                point.setX(point.getX() + x);
                point.setY(point.getY() + y);
                point.setZ(point.getZ() + z);
            }
            
    for(Group group : Group::subGroups)
        group.translate(x, y, z);
}

void Group::rotate(float angle, float x, float y, float z) {

}

void Group::scale(float x, float y, float z) {

}

Camera World::getCamera() {
    return camera;
}

Group World::getGroup() {
    return group;
}

void World::addModel(Model model) {
    World::group.addModel(model);
}

int World::parseXML(string path, string filename) {
    string file = path + filename;
    cout << "Loading " << file << "." << endl;
    XMLDocument doc;
    if(!doc.LoadFile(file.c_str())){
        XMLElement * cameraElem = doc.FirstChildElement("world")->FirstChildElement("camera");
        XMLElement * groupElem = doc.FirstChildElement("world")->FirstChildElement("group");
        
        World::parseCamera(cameraElem);
        World::parseGroup(path, groupElem, );

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

    float fov, near, far;
    XMLElement * projectionElem = elem->FirstChildElement("projection");
    projectionElem->QueryFloatAttribute("fov", &fov);
    projectionElem->QueryFloatAttribute("near", &near);
    projectionElem->QueryFloatAttribute("far", &far);
    World::camera.setFov(fov);
    World::camera.setNear(near);
    World::camera.setFar(far);
}

void World::parseGroup(string path, XMLElement * elem, Group group) {
    for(XMLElement * child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
        string val = child->Value();
        if(val == "models")
            parseModels(path, child);
        else if(child->Value() == "group")
            parseGroup(path, child);
        else if()
    }
    World::group = group;
}

void World::parseModels(string path, XMLElement * elem) {
    for(XMLElement * child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
        string val = child->Value();
        if(val == "model") {
            string filename = child->Attribute("file");
            Model model;
            cout << path << filename << " model loaded." << endl;
            model.readModel(path + filename);
            World::addModel(model);
        }
    }
}

void Model::drawModel() {
    for(Patch patch : getPatches()) {
        vector<Point> primitives = patch.getPoints();
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < primitives.size(); i++) {
                glColor3f(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                          static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                          static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

                Point point = primitives[i];

                glVertex3f(point.getX(), point.getY(), point.getZ());
        }
        glEnd();
    }
}
