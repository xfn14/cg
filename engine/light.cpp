#include "light.h"

float * ModelColor::getDiffuse() {
    return ModelColor::diffuse;
}
        
float * ModelColor::getAmbient() {
    return ModelColor::ambient;
}

float * ModelColor::getSpecular() {
    return ModelColor::specular;
}

float * ModelColor::getEmission() {
    return ModelColor::emission;
}

float ModelColor::getShininess() {
    return ModelColor::shininess;
}

Light::Light(Type type, Point pos) {
    Light::type = type;
    Light::pos = pos;
    Light::cutoff = -1;
}

Light::Light(Point pos, Point dir, int cutoff) {
    Light::type = SPOTLIGHT;
    Light::pos = pos;
    Light::dir = dir;
    Light::cutoff = cutoff;
}

Point Light::getPosition() {
    return Light::pos;
}

Point Light::getDirection() {
    return Light::dir;
}

int Light::getCutoff() {
    return Light::cutoff;
}
