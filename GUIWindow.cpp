#include "GUIWindow.h"
#include "Globals.h"

int GUIWindow::width = 512;   // set window width in pixels here
int GUIWindow::height = 512;   // set window height in pixels here

int GUIWindow::windowID = 0;
GLUI *GUIWindow::GUIMain = nullptr;
GLUI_Panel *GUIWindow::eyePanel = nullptr;
GLUI_Panel *GUIWindow::lookatPanel = nullptr;
GLUI_Panel *GUIWindow::upPanel = nullptr;

GUIWindow::GUIWindow() {}

GUIWindow::~GUIWindow() {}

// Dependency Injection. If GLUI doesn't exist, use GLUT's bindings
void GUIWindow::init(GLUI *Gui, int GLUTWindowID) {
    if( Gui == nullptr ) {
        glutIdleFunc(GUIWindow::idleCallback);
        return;
    }
    GUIMain = Gui;
    windowID = GLUTWindowID;
    GUIMain->set_main_gfx_window(windowID);
    GLUI_Master.set_glutIdleFunc(GUIWindow::idleCallback);
    
    new GLUI_StaticText(GUIMain, "Camera Controls");
    
    eyePanel = new GLUI_Panel(GUIMain, "Eye");
    new GLUI_Spinner(eyePanel, "X", GLUI_SPINNER_FLOAT, 10, GUIWindow::controlCallback);
    new GLUI_Spinner(eyePanel, "Y", GLUI_SPINNER_FLOAT, 10, GUIWindow::controlCallback);
    new GLUI_Spinner(eyePanel, "Z", GLUI_SPINNER_FLOAT, 10, GUIWindow::controlCallback);
    
    lookatPanel = new GLUI_Panel(GUIMain, "Look At");
    new GLUI_Spinner(lookatPanel, "X", GLUI_SPINNER_FLOAT, 11, GUIWindow::controlCallback);
    new GLUI_Spinner(lookatPanel, "Y", GLUI_SPINNER_FLOAT, 11, GUIWindow::controlCallback);
    new GLUI_Spinner(lookatPanel, "Z", GLUI_SPINNER_FLOAT, 11, GUIWindow::controlCallback);

    upPanel = new GLUI_Panel(GUIMain, "Up");
    new GLUI_Spinner(upPanel, "X", GLUI_SPINNER_FLOAT, 12, GUIWindow::controlCallback);
    new GLUI_Spinner(upPanel, "Y", GLUI_SPINNER_FLOAT, 12, GUIWindow::controlCallback);
    new GLUI_Spinner(upPanel, "Z", GLUI_SPINNER_FLOAT, 12, GUIWindow::controlCallback);
}

void GUIWindow::shutdown() {
    free(eyePanel);
    free(upPanel);
    free(lookatPanel);
    free(GUIMain);
}

void GUIWindow::controlCallback(int control) {
    GLUI_Spinner *p1, *p2, *p3;
    
    switch( control ) {
        case 10:
            p1 = (GLUI_Spinner *)eyePanel->first_child();
            p2 = (GLUI_Spinner *)p1->next();
            p3 = (GLUI_Spinner *)p2->next();
            Globals::camera.e.x = p1->get_float_val();
            Globals::camera.e.y = p2->get_float_val();
            Globals::camera.e.z = p3->get_float_val();
        break;
        case 11:
            p1 = (GLUI_Spinner *)lookatPanel->first_child();
            p2 = (GLUI_Spinner *)p1->next();
            p3 = (GLUI_Spinner *)p2->next();
            Globals::camera.d.x = p1->get_float_val();
            Globals::camera.d.y = p2->get_float_val();
            Globals::camera.d.z = p3->get_float_val();
            break;
        case 12:
            p1 = (GLUI_Spinner *)upPanel->first_child();
            p2 = (GLUI_Spinner *)p1->next();
            p3 = (GLUI_Spinner *)p2->next();
            Globals::camera.up.x = p1->get_float_val();
            Globals::camera.up.y = p2->get_float_val();
            Globals::camera.up.z = p3->get_float_val();
            break;
        default: return;
    }
    
}

void GUIWindow::idleCallback(void) {
    if( GUIMain != nullptr && glutGetWindow() != windowID )
        glutSetWindow(windowID);
    
    Globals::camera.update();
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
    
    glLoadMatrixf(Globals::camera.getInverseMatrix().getPointer());
    InputController::getInstance()->poly->draw();
    
    glPopMatrix();
    glFlush();
    
    glutSwapBuffers();
}




