#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Matrix4.h"
#include "Vector3.h"

class Camera {
public:
    Camera(void);
    ~Camera(void);

    Matrix4& getMatrix(void);
    Matrix4& getInverseMatrix(void);
    void update(void);
    void lookAt(Vector3&, Vector3&, Vector3&);
    
    Vector3 e;   //Center of Projection
    Vector3 d;   //Look At
    Vector3 up;  //Up Vector ^
    
protected:
    Matrix4 c;   //Camera Matrix
    Matrix4 ci;  //Inverse of Camera Matrix
    
};

#endif
