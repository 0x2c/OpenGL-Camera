#include "Vector3.h"
#include <Math.h>

Vector3::Vector3() {
    x = y = z = 0.f;
}

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator+(const Vector3 &v) const {
    return Vector3( x+v.x, y+v.y, z+v.z );
}

Vector3 Vector3::operator-(const Vector3 &v) const {
    return Vector3( x-v.x, y-v.y, z-v.z );
}

Vector3 Vector3::operator-() const {
    return Vector3( -x, -y, -z );
}

void Vector3::negate() {
    x = -x;
    y = -y;
    z = -z;
}

Vector3 Vector3::operator*(GLfloat s) const {
    return Vector3( x*s, y*s, z*s );
}

GLfloat Vector3::dot(const Vector3 &v) const {
    return ( x*v.x + y*v.y + z*v.z );
}

Vector3 Vector3::cross(const Vector3 &v) const {
    return Vector3( y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x );
}

void Vector3::scale(GLfloat s) {
    x *= s;
    y *= s;
    z *= s;
}

void Vector3::scale(GLfloat sx, GLfloat sy, GLfloat sz) {
    x *= sx;
    y *= sy;
    z *= sz;
}

void Vector3::scale(const Vector3 &s) {
    x *= s.x;
    y *= s.y;
    z *= s.z;
}

GLfloat Vector3::length() const {
    return sqrt(x*x + y*y + z*z);
}

void Vector3::normalize() {
    GLfloat l = length();
    if( l != 0 ) scale(1 / l);
}

void Vector3::print(std::string comment) {
    std::cout << comment << std::endl;
    std::cout << "Vec3(" << x << ", " << y << ", " << z << ")" << std::endl;
}