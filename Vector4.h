#ifndef __VEC4_H__
#define __VEC4_H__
#include <cstdlib>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <iostream>
#include <string>

class Vector4 {
public:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
    
    Vector4();
    Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    Vector4 operator+(const Vector4&) const;
    Vector4 operator-(const Vector4&) const;
    Vector4 operator-() const;
    void dehomogenize();
    void print(std::string comment);
};



#endif
