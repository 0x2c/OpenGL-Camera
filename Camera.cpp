#include "Camera.h"

Camera::Camera() {
    c.identity();
    
    e = Vector3(0.0, 0.0, 20.0);
    d = Vector3(0.0, 0.0, 0.0);
    up = Vector3(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.makeIdentity().setTranslate(Vector3(e.x, e.y, e.z));
    ci.makeIdentity().setTranslate(Vector3(-e.x, -e.y, -e.z));
}

Camera::~Camera() {}

Matrix4& Camera::getMatrix() {
    return c;
}

Matrix4& Camera::getInverseMatrix() {
    return ci;
}

void Camera::update() {
    c.makeIdentity();
    ci.makeIdentity();
    
    
}

void Camera::lookAt(Vector3& e, Vector3& d, Vector3& up) {
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
