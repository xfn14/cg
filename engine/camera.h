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
        Camera(){
            setPosition(new Point(5, 2, 5));
            setLookAt(new Point(0, 0, 0));
            setUp(new Point(0, 1, 0));
            Camera::fov = 60;
            Camera::near = 1;
            Camera::far = 1000;
        }
        
        Point getPosition();
        void setPosition(Point * position);
        void addPosition(float x, float y, float z);
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