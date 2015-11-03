#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "Camera.h"
#include "Cube.h"
#include "House.h"
#include "OBJEntity.h"
#include "InputController.h"
#include "GUIWindow.h"


class Globals {
public:
    static Camera camera;
    static Cube cube;
    static House house;
    static OBJEntity bunny;
    static OBJEntity dragon;
    static OBJEntity bear;
    static GUIWindow gWindow;
};



#endif