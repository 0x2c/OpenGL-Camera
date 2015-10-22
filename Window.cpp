#include <iostream>
#include "Globals.h"
#include "Window.h"

int Window::width = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback() {
    Globals::cube.spin(0.5);
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h);  // set new viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback() {
    
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
