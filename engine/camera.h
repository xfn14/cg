#ifndef _CAMERA_
#define _CAMERA_

#include <string>

#include "../utils/point.h"

using namespace std;

class Camera {
    private:
        Point position, lookAt, up;
        float fov, near, far;

    public:
        Camera();
        Point getPosition();
        void setPosition(Point * position);
        Point getLookAt();
        void setLookAt(Point * lookAt);
        Point getUp();
        void setUp(Point * up);
        float getFov();
        void setFov(float fov);
        float getNear();
        void setNear(float near);
        float getFar();
        void setFar(float far);
        string toString();
};

#endif