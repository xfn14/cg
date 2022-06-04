#include "world.h"

void Model::setColor(ModelColor color) {
    Model::color = color;
}

ModelColor Model::getColor() {
    return Model::color;
}

vector<Light> World::getLights() {
    return World::lights;
}

void World::addLight(Light light) {
    World::lights.push_back(light);
}

void World::addPositionCamera(float x, float y, float z) {
    World::camera.addPosition(x, y, z);
}

void Group::addModel(Model model) {
    Group::models.push_back(model);
}

vector<Model> Group::getModels() {
    return Group::models;
}

void Group::addTranslate(Translate translate) {
    Group::translates.push_back(translate);
}

vector<Translate> Group::getTranslate() {
    return Group::translates;
}

void Group::addRotate(Rotate rotate) {
    Group::rotates.push_back(rotate);
}

vector<Rotate> Group::getRotate() {
    return Group::rotates;
}

void Group::addScale(Scale scale) {
    Group::scales.push_back(scale);
}

vector<Scale> Group::getScale() {
    return Group::scales;
}

Color Group::getColor() {
    return Group::color;
}

void Group::setColor(Color c) {
    Group::color = c;
}

void Group::addGroup(Group group) {
    Group::subGroups.push_back(group);
}

vector<Group> Group::getGroups() {
    return Group::subGroups;
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
    for(Model model : Group::models)
        for(Patch patch : model.getPatches())
            for(Point point : patch.getPoints()) {
                if(x == 1){
                    float yy = point.getY()*cosf(angle) - point.getZ()*sinf(angle);
                    float zz = point.getY()*sinf(angle) + point.getZ()*cosf(angle);
                    point.setX(point.getX());
                    point.setY(yy);
                    point.setZ(zz);
                }
                if(y == 1){
                    float xx = point.getX()*cosf(angle) + point.getZ()*sinf(angle);
                    float zz = - point.getX()*sinf(angle) + point.getZ()*cosf(angle);
                    point.setX(xx);
                    point.setY(point.getY());
                    point.setZ(zz);
                }
                if(z == 1){
                    float xx = point.getX()*cosf(angle) - point.getY()*sinf(angle);
                    float yy = point.getX()*sinf(angle) + point.getY()*cosf(angle);
                    point.setX(xx);
                    point.setY(yy);
                    point.setZ(point.getZ());
                }
            }
        
    for(Group group : Group::subGroups)
        group.rotate(angle, x, y, z);
}

void Group::scale(float x, float y, float z) {
    for(Model model : Group::models)
        for(Patch patch : model.getPatches())
            for(Point point : patch.getPoints()) {
                point.setX(point.getX() * x);
                point.setY(point.getY() * y);
                point.setZ(point.getZ() * z);
            }
            
    for(Group group : Group::subGroups)
        group.scale(x, y, z);
}

Camera World::getCamera() {
    return World::camera;
}

Group* World::getGroup() {
    return World::group;
}

void World::addModel(Model model) {
    World::group->addModel(model);
}

int World::parseXML(string path, string filename) {
    string file = path + filename;
    cout << "Loading " << file << "." << endl;
    XMLDocument doc;
    if(!doc.LoadFile(file.c_str())){
        XMLElement * cameraElem = doc.FirstChildElement("world")->FirstChildElement("camera");
        XMLElement * groupElem = doc.FirstChildElement("world")->FirstChildElement("group");
        XMLElement * lightElem = doc.FirstChildElement("world")->FirstChildElement("light");

        World::parseCamera(cameraElem);

        if (lightElem != NULL)
            World::parseLights(lightElem);

        Group *g = (new Group());
        World::parseGroup(path, groupElem, g);
        World::group = g;

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

void World::parseLights(XMLElement * elem) {
    for(XMLElement * child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
        if(strcmp(child->Value(), "light") == 0){
            const char * type;
            child->QueryStringAttribute("type", &type);
            if(strcmp(type, "point") == 0) {
                float posX, posY, posZ;
                child->QueryFloatAttribute("posX", &posX);
                child->QueryFloatAttribute("posY", &posY);
                child->QueryFloatAttribute("posZ", &posZ);
                World::lights.push_back(*(new Light(POINT, *(new Point(posX, posY, posZ)))));
            } else if(strcmp(type, "directional") == 0) {
                float dirX, dirY, dirZ;
                child->QueryFloatAttribute("dirX", &dirX);
                child->QueryFloatAttribute("dirY", &dirY);
                child->QueryFloatAttribute("dirZ", &dirZ);
                World::lights.push_back(*(new Light(DIRECTIONAL, *(new Point(dirX, dirY, dirZ)))));
            } else if(strcmp(type, "spotlight") == 0) {
                float posX, posY, posZ, dirX, dirY, dirZ;
                int cutoff;
                child->QueryFloatAttribute("posX", &posX);
                child->QueryFloatAttribute("posY", &posY);
                child->QueryFloatAttribute("posZ", &posZ);
                child->QueryFloatAttribute("dirX", &dirX);
                child->QueryFloatAttribute("dirY", &dirY);
                child->QueryFloatAttribute("dirZ", &dirZ);
                child->QueryIntAttribute("cutoff", &cutoff);
                World::lights.push_back(*(new Light(*(new Point(posX, posY, posZ)), *(new Point(dirX, dirY, dirZ)), cutoff)));	
            }
        }
    }
}

void World::parseGroup(string path, XMLElement * elem, Group *g) {
    for(XMLElement * child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
        if(strcmp(child->Value(), "models") == 0) // Load models
            parseModels(path, child, g);

        if(strcmp(child->Value(), "group") == 0) {
            Group *subGroup = (new Group());
            parseGroup(path, child, subGroup);
            g->addGroup(*subGroup);
        }

        if(strcmp(child->Value(), "transform") == 0)
            World::parseTransform(child, g);
    }

}

void World::parseModels(string path, XMLElement * elem, Group * g) {
    for(XMLElement * child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
        if(strcmp(child->Value(), "model") == 0) {
            string filename = child->Attribute("file");
            Model model;
            cout << path << filename << " model loaded." << endl;
            model.readModel(path + filename);

            // Load model color and textures
            for(XMLElement * modelChild = child->FirstChildElement(); modelChild != NULL; modelChild = modelChild->NextSiblingElement()){
                if(modelChild->Value() == "color") {
                    // Check if RGB values need to be between 0-1
                    float diffuse[4] = {200, 200, 200, 1};
                    float ambient[4] = {50, 50, 50, 1};
                    float specular[4] = {0, 0, 0, 1};
                    float emissive[4] = {0, 0, 0, 1};
                    float shine = 0;

                    XMLElement * diffElem = modelChild->FirstChildElement("diffuse");
                    XMLElement * ambElem = modelChild->FirstChildElement("ambient");
                    XMLElement * specElem = modelChild->FirstChildElement("specular");
                    XMLElement * emiElem = modelChild->FirstChildElement("emissive");

                    diffElem->QueryFloatAttribute("R", &diffuse[0]);
                    diffElem->QueryFloatAttribute("G", &diffuse[1]);
                    diffElem->QueryFloatAttribute("B", &diffuse[2]);

                    ambElem->QueryFloatAttribute("R", &ambient[0]);
                    ambElem->QueryFloatAttribute("G", &ambient[1]);
                    ambElem->QueryFloatAttribute("B", &ambient[2]);

                    specElem->QueryFloatAttribute("R", &specular[0]);
                    specElem->QueryFloatAttribute("G", &specular[1]);
                    specElem->QueryFloatAttribute("B", &specular[2]);

                    emiElem->QueryFloatAttribute("R", &emissive[0]);
                    emiElem->QueryFloatAttribute("G", &emissive[1]);
                    emiElem->QueryFloatAttribute("B", &emissive[2]);

                    modelChild->QueryFloatAttribute("shine", &shine);

                    model.setColor(*(new ModelColor(diffuse, ambient, specular, emissive, shine)));
                } else if(modelChild->Value() == "texture") {
                    string textPath = modelChild->Attribute("file");
                    model.loadTexture(path + textPath);
                }
            }

            model.initVbo();
            g->addModel(model);
        }
    }
}

void World::parseTransform(XMLElement * elem, Group *g) {
    for(XMLElement * child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
        if(strcmp(child->Value(), "rotate") == 0) {
            float angle, x, y, z;
            int time;
            child->QueryFloatAttribute("x", &x);
            child->QueryFloatAttribute("y", &y);
            child->QueryFloatAttribute("z", &z);
            if(child->Attribute("time") != NULL){
                child->QueryIntAttribute("time", &time);
                g->addRotate(*(new Rotate(time, x, y, z)));
            } else {
                child->QueryFloatAttribute("angle", &angle);
                g->addRotate(*(new Rotate(angle, x, y, z)));
            }
        } else if(strcmp(child->Value(), "translate") == 0) {
            Translate translate;
            if(child->Attribute("x") != NULL) {
                float x, y, z;
                child->QueryFloatAttribute("x", &x);
                child->QueryFloatAttribute("y", &y);
                child->QueryFloatAttribute("z", &z);
                translate = *(new Translate(x, y, z));
            } else {
                float time;
                bool align = false;
                child->QueryFloatAttribute("time", &time);
                if(child->Attribute("align") != NULL)
                    child->QueryBoolAttribute("align", &align);
                translate = *(new Translate(time, align));
                for(XMLElement * child2 = child->FirstChildElement(); child2 != NULL; child2 = child2->NextSiblingElement()){
                    if(strcmp(child2->Value(), "point") == 0) {
                        float x2, y2, z2;
                        child2->QueryFloatAttribute("x", &x2);
                        child2->QueryFloatAttribute("y", &y2);
                        child2->QueryFloatAttribute("z", &z2);
                        translate.addPoint(*(new Point(x2, y2, z2)));
                    }
                }
            }
            g->addTranslate(translate);
        } else if(strcmp(child->Value(), "scale") == 0) {
            float x, y, z;
            child->QueryFloatAttribute("x", &x);
            child->QueryFloatAttribute("y", &y);
            child->QueryFloatAttribute("z", &z);
            g->addScale(*(new Scale(x, y, z)));
        }
        else if(strcmp(child->Value(), "color") == 0) {
            float r, gg, b;
            child->QueryFloatAttribute("r", &r);
            child->QueryFloatAttribute("g", &gg);
            child->QueryFloatAttribute("b", &b);
            g->setColor(*(new Color(r, gg, b)));
        }
    }
}

void Model::initVbo() {
    int size = 0;
    for(Patch patch : patches)
        size += patch.getPoints().size();
    float* arr_vert = (float*) malloc(sizeof(float) * size * 3);
    float* arr_norm = (float*) malloc(sizeof(float) * size * 3);
    float* arr_text = (float*) malloc(sizeof(float) * size * 2);

    int i;
    for(Patch patch : patches)
        for (i = 0; i < patch.getPoints().size(); ++i) {
            arr_vert[i * 3] = patch.getPoints()[i].getX();
            arr_vert[i * 3 + 1] = patch.getPoints()[i].getY();
            arr_vert[i * 3 + 2] = patch.getPoints()[i].getZ();

            arr_norm[i * 3] = patch.getNormals()[i].getX();
            arr_norm[i * 3 + 1] = patch.getNormals()[i].getY();
            arr_norm[i * 3 + 2] = patch.getNormals()[i].getZ();

            arr_text[i * 2] = patch.getTexture()[i].getX();
            arr_text[i * 2 + 1] = patch.getTexture()[i].getY();
        }

    glGenBuffers(1, &vboId);
    glGenBuffers(1, &normalsId);
    glGenBuffers(1, &textureId);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i * 3, arr_vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalsId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i * 3, arr_norm, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, textureId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i * 2, arr_text, GL_STATIC_DRAW);

    free(arr_vert);
    free(arr_norm);
    free(arr_text);
}

void Model::drawModel(Color color) {
    int size = 0;
    for(Patch patch : patches)
        size += patch.getPoints().size();

    ModelColor modelColor = Model::getColor();
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, modelColor.getDiffuse());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, modelColor.getAmbient());
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, modelColor.getEmission());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, modelColor.getSpecular());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, modelColor.getShininess());

    // glColor3f(color.getR(), color.getG(), color.getB());
    
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalsId);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, textureId);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDrawArrays(GL_TRIANGLES, 0, size);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // for(Patch patch : getPatches()) {
    //     vector<Point> primitives = patch.getPoints();
    //     glBegin(GL_TRIANGLES);
    //     //glBegin(GL_LINE_STRIP);

    //     for (int i = 0; i < primitives.size(); i++) {
    //         // glColor3f(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
    //         //           static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
    //         //           static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    //         Point point = primitives[i];
    //         glColor3f(color.getR(), color.getG(), color.getB());
    //         glVertex3f(point.getX(), point.getY(), point.getZ());
    //     }
    //     glEnd();
    // }
}

void Model::loadTexture(string path) {
    unsigned int t, tw, th;
    unsigned char *texData;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring) path.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
}
