#include "input.h"

#include <iostream>

#define SHIFT_BOOST 1.5f
#define MOUSE_DRAG_COEFF 0.05f

namespace copakond {
    Input::Input(Camera &cam, int winWidth, int winHeight) : _camera(cam), _winWidth(winWidth), _winHeight(winHeight) {
    }

    void Input::screenResize(int winWidth, int winHeight) {
        _winWidth = winWidth;
        _winHeight = winHeight;
    }

    // saving input to key map once some key is pressed and unpressed
    void Input::keyboardInputEvent(unsigned char key, int x, int y) {
        keysMap[std::tolower(key)] = true;
        keysMap[std::toupper(key)] = true;
    }

    void Input::keyboardUpInputEvent(unsigned char key, int x, int y) {
        keysMap[std::tolower(key)] = false;
        keysMap[std::toupper(key)] = false;
    }

    void Input::specKeyboardInputEvent(int key, int x, int y) {
        keysMap[key + IS_SPECIAL_KEY] = true;

        if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R) { keysMap[KEY_SHIFT] = true; }
        if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) { keysMap[KEY_SHIFT] = true; }
    }

    void Input::specKeyboardUpInputEvent(int key, int x, int y) {
        keysMap[key + IS_SPECIAL_KEY] = false;

        if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R) { keysMap[KEY_SHIFT] = false; }
        if (!(glutGetModifiers() & GLUT_ACTIVE_SHIFT)) { keysMap[KEY_SHIFT] = false; }
    }

    // LMB, RMB, MMB
    void Input::mouseButtonEvent(int button, int state, int x, int y) {
        if (button == GLUT_MIDDLE_BUTTON) {
            if (state == GLUT_DOWN) {
                keysMap[MOUSE_BUTTON_RIGHT] = true;
            } else if (state == GLUT_UP) {
                keysMap[MOUSE_BUTTON_RIGHT] = false;
            }
        }
    }

    // mouse movement - changing yaw and pitch
    void Input::mouseMoveEvent(int x, int y) {
        int centerX = _winWidth / 2;
        int centerY = _winHeight / 2;

        if (x == centerX && y == centerY) return;

        mouseDeltaX = static_cast<float>(x - centerX);
        mouseDeltaY = static_cast<float>(centerY - y);

        glutWarpPointer(centerX, centerY);

        if (_firstMouseMovement == false) {
            _firstMouseMovement = true;
            mouseDeltaX = 0;
            mouseDeltaY = 0;
        }

        glutPostRedisplay();
    }

    void Input::mouseWheelEvent(int wheel, int direction, int x, int y) {}
}
