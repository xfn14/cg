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

float Camera::getFov() {
    return fov;
}

void Camera::setFov(float fov) {
    Camera::fov = fov;
}

float Camera::getNear() {
    return near;
}

void Camera::setNear(float near) {
    Camera::near = near;
}

float Camera::getFar() {
    return far;
}

void Camera::setFar(float far) {
    Camera::far = far;
}