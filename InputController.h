#ifndef __INPUTCTRL_H__
#define __INPUTCTRL_H__

#include "Drawable.h"

enum DisplayMode {
    CUBE = 0,
    HOUSE1 = 1,
    HOUSE2 = 2
};

class InputController {
public:
    static InputController* getInstance();
    static void keyboardCallback(unsigned char key, int mouse_x, int mouse_y);
    static void skeyboardCallback(int key, int x, int y);

    DisplayMode mode;		// Current Display Mode
    Drawable *poly;
    
private:
    InputController();
    static InputController *instance;	// Singleton Instance
};

#endif
