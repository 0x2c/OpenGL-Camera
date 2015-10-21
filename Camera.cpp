#include "Camera.h"

Camera::Camera() {
    c.identity();
    
    e = Vector3(0.0, 0.0, 20.0);
    d = Vector3(0.0, 0.0, 0.0);
    up = Vector3(0.0, 1.0, 0.0);

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
    
    Matrix4 Ri = Matrix4({
        {x.x, y.x, z.x, 0},
        {x.y, y.y, z.y, 0},
        {x.z, y.z, z.z, 0},
        { 0 ,  0 ,  0 , 0}
    });
    
    Matrix4 Ti = Matrix4({
        {  1,   0,    0,   0},
        {  0,   1,    0,   0},
        {  0,   0,    1,   0},
        {-e.x, -e.y, -e.z, 1}
    });
    
    c = Ri.setTranslate(e);
    ci = Ri * Ti;
}

void Camera::lookAt(Vector3& e, Vector3& d, Vector3& up) {
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
