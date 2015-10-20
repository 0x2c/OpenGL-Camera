#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "defs.h"

class Window {    
public:
    static int width;
    static int height;
    
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif
