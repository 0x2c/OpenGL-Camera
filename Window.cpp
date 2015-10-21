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

static int animateDT = 0;
static int animateT = 500;
static Vector3 eye_position = Vector3(0,0,-20);
//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    
    animateDT++;
    if( animateDT >= animateT ) {
        eye_position.z -= 0.1;
        animateDT = 0;
    }
    
    glPushMatrix();
    glLoadMatrixf(Matrix4::transpose(Globals::camera.getInverseMatrix()).getPointer());
    Globals::cube.draw();
    
    glPopMatrix();
    glFlush();
    
    glutSwapBuffers();
}
