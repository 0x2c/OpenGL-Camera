#ifndef __CUBE_H__
#define __CUBE_H__

#include "Matrix4.h"
#include "Drawable.h"


class Cube : public Drawable {
public:
    Cube();   // Constructor
    virtual ~Cube();
    Matrix4& getMatrix();
    
    virtual void draw();
};

#endif
