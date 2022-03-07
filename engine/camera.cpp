#include "camera.h"

Camera::Camera(){
    setPosition(new Point(0, 0, 0));
    setLookAt(new Point(0, 0, 0));
    setUp(new Point(0, 0, 0));
    Camera::fov = 0;
    Camera::near = 0;
    Camera::far = 0;
}

Point Camera::getPosition() {
    return position;
}

void Camera::setPosition(Point * position) {
    Camera::position = *position;
}

Point Camera::getLookAt() {
    return lookAt;
}

void Camera::setLookAt(Point * lookAt) {
    Camera::lookAt = *lookAt;
}

Point Camera::getUp() {
    return up;
}

void Camera::setUp(Point * up) {
    Camera::up = *up;
}

int Camera::getFov() {
    return fov;
}

void Camera::setFov(int fov) {
    Camera::fov = fov;
}

int Camera::getNear() {
    return near;
}

void Camera::setNear(int near) {
    Camera::near = near;
}

int Camera::getFar() {
    return far;
}

void Camera::setFar(int far) {
    Camera::far = far;
}