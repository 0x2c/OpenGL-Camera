#include "Camera.h"

Camera::Camera() {
    c.identity();
    
    e = Vector3(0.0, 0.0, 20.f);
    d = Vector3(0.0, 0.0, 0.0);
    up = Vector3(0.0, 1.f, 0.0);

    c.makeIdentity().setTranslate(Vector3(e.x, e.y, e.z));
    ci.makeIdentity().setTranslate(Vector3(e.x, e.y, -e.z));
}

Camera::~Camera() {}

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
    Matrix4 Ri = c = Matrix4({
        {x.x, y.x, z.x, 0.0},
        {x.y, y.y, z.y, 0.0},
        {x.z, y.z, z.z, 0.0},
        {0.0, 0.0, 0.0, 1.f}
    });
    Matrix4 Ti = Matrix4({
        {1.f, 0.0, 0.0, -e.x},
        {0.0, 1.f, 0.0, -e.y},
        {0.0, 0.0, 1.f, -e.z},
        {0.0, 0.0, 0.0,  1.f}
    });
    c.setTranslate(e);
    ci = Ri.makeTranspose() * Ti;
}

void Camera::lookAt(const Vector3& e,const Vector3& d,const Vector3& up) {
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
