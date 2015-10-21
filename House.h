#ifndef __HOUSE_H__
#define __HOUSE_H__

#include <cstdlib>
#include <GLUT/glut.h>
#include "Drawable.h"

class House : public Drawable {
public:
    House();
    ~House();
    virtual void draw();
    
private:
    GLint nVerts;
    GLint *indices;
    GLfloat *vertices;
    GLfloat *colors;
};


#endif
