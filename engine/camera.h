#ifndef _CAMERA_
#define _CAMERA_

#include <string>

#include "../utils/point.h"

using namespace std;

class Camera {
    private:
        Point position, lookAt, up;
        int fov, near, far;

    public:
        Camera();
        Point getPosition();
        void setPosition(Point * position);
        Point getLookAt();
        void setLookAt(Point * lookAt);
        Point getUp();
        void setUp(Point * up);
        int getFov();
        void setFov(int fov);
        int getNear();
        void setNear(int near);
        int getFar();
        void setFar(int far);
        string toString();
};

#endif