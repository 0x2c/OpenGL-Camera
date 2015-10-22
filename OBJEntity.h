#ifndef __OBJENTITY_H__
#define __OBJENTITY_H__

#include <cstdlib>
#include <GLUT/glut.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

#include "Vector3.h"
#include "Drawable.h"

struct Face {
    GLint vertexIndices[3];
    GLint normalIndices[3];
    
    Face(){}
    
    void set(int v0, int v1, int v2, int n0, int n1, int n2) {
        vertexIndices[0] = v0;
        vertexIndices[1] = v1;
        vertexIndices[2] = v2;
        normalIndices[0] = n0;
        normalIndices[1] = n1;
        normalIndices[2] = n2;
    }
};


class OBJEntity : public Drawable {
protected:
    //Storage vectors
    std::vector<Vector3*>* vertices;
    std::vector<Vector3*>* colors;
    std::vector<Vector3*>* normals;
    
    std::vector<Face*>* faces;

    void parse(const char* filename);

    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
public:
    
    OBJEntity(std::string filename);
    virtual ~OBJEntity();
    
    virtual void draw();
    virtual void update();
};

#endif
