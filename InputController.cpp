#include "InputController.h"
#include "Globals.h"

InputController* InputController::instance = NULL;

InputController::InputController() : mode(DisplayMode::CUBE) {
    poly = &Globals::cube;
};

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
            break;
        default:
            return;
    }
}
