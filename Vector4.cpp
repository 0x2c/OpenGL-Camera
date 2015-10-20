#include "Vector4.h"

Vector4::Vector4() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Vector4::Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4 Vector4::operator+(const Vector4& v) const {
    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator-(const Vector4& v) const {
    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4 Vector4::operator-() const {
    return Vector4( -x, -y, -z, -w );
}

void Vector4::dehomogenize() {
    x /= w;
    y /= w;
    z /= w;
    w = 1;
}

void Vector4::print(std::string comment) {
    std::cout << comment << std::endl;
    std::cout << "Vec4(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
}
