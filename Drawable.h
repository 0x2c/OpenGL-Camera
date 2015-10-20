#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <cstdlib>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "Matrix4.h"

class Drawable {
protected:
    int direction;      // direction of spin
    Matrix4 m2w;        // model2world matrix
    
public:
    Drawable();
    ~Drawable();
    
    void toggleDirection();
    void spin(GLfloat deg);
    void orbit(GLfloat deg);
    void translateX(GLfloat units);
    void translateY(GLfloat units);
    void translateZ(GLfloat units);
    void scale(GLfloat x, GLfloat y, GLfloat z);
    void reset();
    
    virtual void draw();
    virtual void update();
};


#endif
