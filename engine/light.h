#ifndef _LIGHT_
#define _LIGHT_

#include "../utils/point.h"

class ModelColor {
    private:
        float diffuse[4], ambient[4], specular[4], emission[4], shininess;

    public:
        ModelColor() {}
        /*
            diffuse{200, 200, 200, 1} ,
            ambient{50, 50, 50, 1} ,
            specular{0, 0, 0, 1} , 
            emission{0, 0, 0, 1} {
            shininess = 0;
        }*/

        ModelColor(float diffuse[4], float ambient[4], float specular[4], float emission[4], float shininess) {
            for(int i = 0; i < 4; ++i) {
                ModelColor::diffuse[i] = diffuse[i];
                ModelColor::ambient[i] = ambient[i];
                ModelColor::specular[i] = specular[i];
                ModelColor::emission[i] = emission[i];
            }
            ModelColor::shininess = shininess;
        }

        float * getDiffuse();
        float * getAmbient();
        float * getSpecular();
        float * getEmission();
        float getShininess();
};

enum Type {
    POINT,
    DIRECTIONAL,
    SPOTLIGHT
};

class Light {
    private:
        Type type;
        Point pos;
        Point dir;
        int cutoff;

    public:
        Light(Type type, Point pos); // For point and directional lights
        Light(Point pos, Point dir, int cutoff); // For spotlight lights
        Point getPosition();
        Point getDirection();
        int getCutoff();
        void render();
};

#endif