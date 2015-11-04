#include "Camera.h"

Camera::Camera() {
    reset();
}

Camera::~Camera() {}


void Camera::reset() {
    e = Vector3(0.0, 0.0, 20.f);
    d = Vector3(0.0, 0.0, 0.0);
    up = Vector3(0.0, 1.f, 0.0);
    update();
}

Matrix4& Camera::getMatrix() {
    return c;
}

Matrix4& Camera::getInverseMatrix() {
    return ci;
}

void Camera::update() {
    Vector3 z,x,y;
    z = e - d;
    z.normalize();
    x = up.cross(z);
    x.normalize();
    y = z.cross(x);
    
    c = Matrix4({
        {x.x, x.y, x.z, 0},
              {y.x, y.y, y.z, 0},
              {z.x, z.y, z.z, 0},
              {e.x, e.y, e.z, 1}
    });
    
    ci = c.rigidInverse();
}

void Camera::lookAt(const Vector3& e,const Vector3& d,const Vector3& up) {
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
