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
        Camera::Camera(){
            setPosition(new Point(0, 0, 0));
            setLookAt(new Point(0, 0, 0));
            setUp(new Point(0, 0, 0));
            Camera::fov = 0;
            Camera::near = 0;
            Camera::far = 0;
        }
        
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