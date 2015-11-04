#include "InputController.h"
#include "Globals.h"

InputController* InputController::instance = NULL;

InputController::InputController() : mode(DisplayMode::CUBE) {
    poly = &Globals::cube;
}

InputController* InputController::getInstance() {
    if( !instance ) instance = new InputController();
    return instance;
}

void InputController::keyboardCallback(unsigned char key, int mouse_x, int mouse_y) {
    if( key == 'q' || key == 'Q' )
        exit(EXIT_SUCCESS);
    else if(getInstance()->poly != NULL ) {
        int direction = -1;
        switch (key) {
            case 'o': direction = -direction;
            case 'O': getInstance()->poly->orbit(direction * 10); break;
            case 't': getInstance()->poly->toggleDirection(); break;
            case 'r': getInstance()->poly->reset(); break;
            case 'X': direction = -direction;   // left/right
            case 'x': getInstance()->poly->translateX(direction); break;
            case 'y': direction = -direction;   // up/down
            case 'Y': getInstance()->poly->translateY(direction); break;
            case 'z': direction = -direction;   // out/in
            case 'Z': getInstance()->poly->translateZ(direction); break;
            case 's': getInstance()->poly->scale(0.95, 0.95, 0.95); break; // smaller
            case 'S': getInstance()->poly->scale(1.05, 1.05, 1.05); break; // bigger
        }
    }
}

void InputController::skeyboardCallback(int key, int mouse_x, int mouse_y) {
    switch( key ) {
        case GLUT_KEY_F1:
            getInstance()->mode = DisplayMode::CUBE;
            getInstance()->poly = &Globals::cube;
            Globals::camera.reset();
            break;
        case GLUT_KEY_F2:
            getInstance()->mode = DisplayMode::HOUSE1;
            getInstance()->poly = &Globals::house;
            Globals::camera.lookAt(Vector3(0,24.14, 24.14), Vector3(0,0,0), Vector3(0,1,0));
            break;
        case GLUT_KEY_F3:
            getInstance()->mode = DisplayMode::HOUSE2;
            getInstance()->poly = &Globals::house;
            Globals::camera.lookAt(Vector3(-28.33,11.66,23.33), Vector3(-5,0,0), Vector3(0,1,0.5));
            break;
        case GLUT_KEY_F4:
            getInstance()->mode = DisplayMode::BUNNY;
            getInstance()->poly = &Globals::bunny;
            Globals::camera.reset();
            break;
        case GLUT_KEY_F5:
            getInstance()->mode = DisplayMode::DRAGON;
            getInstance()->poly = &Globals::dragon;
            Globals::camera.reset();
            break;
        case GLUT_KEY_F6:
            getInstance()->mode = DisplayMode::BEAR;
            getInstance()->poly = &Globals::bear;
            Globals::camera.reset();
        default:
            return;
    }
}
