#ifndef __VEC3_H__
#define __VEC3_H__

#include <cstdlib>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <iostream>
#include <string>

class Vector3 {
public:
    Vector3();
    Vector3(GLfloat x, GLfloat y, GLfloat z);
    Vector3 operator+(const Vector3 &) const;
    Vector3 operator-(const Vector3 &) const;
    Vector3 operator-() const;
    void negate();
    
    Vector3 operator*(GLfloat) const;
    GLfloat dot(const Vector3 &) const;
    Vector3 cross(const Vector3 &) const;
    
    void scale(GLfloat);
    void scale(GLfloat, GLfloat, GLfloat);
    void scale(const Vector3 &);
    
    GLfloat length() const;
    void normalize();
    
    void print(std::string comment);
    
    GLfloat x;
    GLfloat y;
    GLfloat z;
};


#endif
