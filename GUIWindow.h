#ifndef __GUIWINDOW_H__
#define __GUIWINDOW_H__

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <GLUI/glui.h>

class GUIWindow {
public:

    GUIWindow();
    ~GUIWindow();
    void init(GLUI *Gui = nullptr, int GLUTWindowID = 0);
    void shutdown();
    
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);

    static int width;
    static int height;
    
private:
    static int windowID;
    static GLUI * GUIMain;
};

#endif
