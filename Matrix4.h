#ifndef __MAT4_H__
#define __MAT4_H__

#include <cstdlib>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <iostream>
#include <string.h>
#include "Vector3.h"
#include "Vector4.h"

class Matrix4 {
public:
    Matrix4();
    Matrix4(const GLfloat (&el)[4][4]);
    GLfloat* getPointer();
    
    Matrix4 operator*(const Matrix4&) const;
    Vector4 operator*(const Vector4&) const;
    Matrix4& operator=(const Matrix4&);
    
    // Returns reference to self to support chainability
    // Modifies held matrix.
    Matrix4& makeIdentity();
    Matrix4& makeTranspose();
    Matrix4& makeRotateX(GLfloat deg);
    Matrix4& makeRotateY(GLfloat deg);
    Matrix4& makeRotateZ(GLfloat deg);
    Matrix4& makeRotate(GLfloat deg, Vector3 axis);
    
    Matrix4& makeScale(GLfloat x, GLfloat y, GLfloat z);
    Matrix4& makeScale(const Vector3&);
    Matrix4& makeTranslate(GLfloat x, GLfloat y, GLfloat z);
    Matrix4& makeTranslate(const Vector3&);
    Vector3 getTranslate() const;
    Matrix4& setTranslate(const Vector3& v);
        
    // static useful to have when converting to col-major
    static Matrix4 identity();
    static Matrix4 transpose(const Matrix4&);
    
    void print(std::string comment);
    friend std::ostream& operator<<(std::ostream& o, const Matrix4& m);
    
    GLfloat m[4][4];
};


#endif
