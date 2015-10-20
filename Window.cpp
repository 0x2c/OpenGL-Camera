#include <iostream>
#include "Globals.h"
#include "Window.h"

int Window::width = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback() {
    Globals::cube.spin(0.5);
    std::cout << Globals::cube.getMatrix() << std::endl;
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
    glTranslatef(0, 0, -20); //moves camera back 20 units
}


//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);

    Globals::cube.draw();

    glFlush();
    
    glutSwapBuffers();
}
