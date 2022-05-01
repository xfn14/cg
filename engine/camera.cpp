#include "camera.h"

Point Camera::getPosition() {
    return Camera::position;
}

void Camera::setPosition(Point * position) {
    Camera::position = *position;
}

void Camera::addPosition(float x, float y, float z) {
    Camera::position.addX(x);
    Camera::position.addY(y);
    Camera::position.addZ(z);
}

Point Camera::getLookAt() {
    return Camera::lookAt;
}

void Camera::setLookAt(Point * lookAt) {
    Camera::lookAt = *lookAt;
}

Point Camera::getUp() {
    return Camera::up;
}

void Camera::setUp(Point * up) {
    Camera::up = *up;
}

float Camera::getFov() {
    return Camera::fov;
}

void Camera::setFov(float fov) {
    Camera::fov = fov;
}

float Camera::getNear() {
    return Camera::near;
}

void Camera::setNear(float near) {
    Camera::near = near;
}

float Camera::getFar() {
    return Camera::far;
}

void Camera::setFar(float far) {
    Camera::far = far;
}