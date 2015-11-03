#include "GUIWindow.h"
#include "Globals.h"

int GUIWindow::width = 512;   // set window width in pixels here
int GUIWindow::height = 512;   // set window height in pixels here

int GUIWindow::windowID = 0;
GLUI *GUIWindow::GUIMain = nullptr;

GUIWindow::GUIWindow() {}

GUIWindow::~GUIWindow() {}

// Dependency Injection. If GLUI doesn't exist, use GLUT's bindings
void GUIWindow::init(GLUI *Gui, int GLUTWindowID) {
    if( Gui != nullptr ) {
        GUIMain = Gui;
        windowID = GLUTWindowID;
        GUIMain->set_main_gfx_window(windowID);
        GLUI_Master.set_glutIdleFunc(GUIWindow::idleCallback);
    } else {
        glutIdleFunc(GUIWindow::idleCallback);
    }
}

void GUIWindow::shutdown() {
    
}

void GUIWindow::idleCallback(void) {
    if( glutGetWindow() != windowID )
        glutSetWindow(windowID);
    Globals::cube.spin(0.5);
    displayCallback();
}

void GUIWindow::reshapeCallback(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h);  // set new viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);
}

void GUIWindow::displayCallback(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    switch( InputController::getInstance()->mode ) {
            
        case DisplayMode::HOUSE1:
            Globals::camera.lookAt(Vector3(0,24.14, 24.14), Vector3(0,0,0), Vector3(0,1,0));
            break;
        case DisplayMode::HOUSE2:
            Globals::camera.lookAt(Vector3(-28.33,11.66,23.33), Vector3(-5,0,0), Vector3(0,1,0.5));
            break;
        case DisplayMode::CUBE:
        case DisplayMode::BUNNY:
        case DisplayMode::DRAGON:
        case DisplayMode::BEAR:
            Globals::camera.reset();
            break;
    }
    
    glLoadMatrixf( Matrix4::transpose(Globals::camera.getInverseMatrix()).getPointer());
    InputController::getInstance()->poly->draw();
    
    glPopMatrix();
    glFlush();
    
    glutSwapBuffers();
}




