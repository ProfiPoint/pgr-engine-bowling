#include "input.h"

#include <iostream>

#define SHIFT_BOOST 1.5f
#define MOUSE_DRAG_COEFF 0.05f

namespace copakond {
    Input::Input(Camera &cam, int winWidth, int winHeight) : _camera(cam), _winWidth(winWidth), _winHeight(winHeight) {
    }

    void Input::update(int winWidth, int winHeight) {
        _winWidth = winWidth;
        _winHeight = winHeight;
    }

    // saving input to key map once some key is pressed and unpressed
    void Input::keyboardInputEvent(unsigned char key, int x, int y) {
        _keysMap[std::tolower(key)] = true;
        _keysMap[std::toupper(key)] = true;

        if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) _keysMap[KEY_SHIFT] = true;
    }

    void Input::specKeyboardInputEvent(int key, int x, int y) {
        _keysMap[key + 256] = true;

        if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) _keysMap[KEY_SHIFT] = true;
    }

    void Input::keyboardUpInputEvent(unsigned char key, int x, int y) {
        _keysMap[std::tolower(key)] = false;
        _keysMap[std::toupper(key)] = false;

        if (!(glutGetModifiers() & GLUT_ACTIVE_SHIFT)) {
            _keysMap[KEY_SHIFT] = false;
        }
    }

    void Input::specKeyboardUpInputEvent(int key, int x, int y) {
        _keysMap[key + 256] = false;

        if (!(glutGetModifiers() & GLUT_ACTIVE_SHIFT)) {
            _keysMap[KEY_SHIFT] = false;
        }
    }

    // parsing key movement WASD / arrows
    void Input::keyInput(float deltaTime) {
        if (_keysMap[KEY_SHIFT]) { shiftSpeedBoost = SHIFT_BOOST;  } else { shiftSpeedBoost = 1.0f; }
        float speed = deltaTime * shiftSpeedBoost;
        glm::vec3 direction(0.0f);

        if (_keysMap['w'] || _keysMap[GLUT_KEY_UP + IS_SPECIAL_KEY]) { direction.z += 1.0f; }
        if (_keysMap['s'] || _keysMap[GLUT_KEY_DOWN + IS_SPECIAL_KEY]) { direction.z -= 1.0f; }
        if (_keysMap['a'] || _keysMap[GLUT_KEY_LEFT + IS_SPECIAL_KEY]) { direction.x -= 1.0f; }
        if (_keysMap['d'] || _keysMap[GLUT_KEY_RIGHT + IS_SPECIAL_KEY]) { direction.x += 1.0f; }
        if (_keysMap['e']) { direction.y += 1.0f; }
        if (_keysMap['q']) { direction.y -= 1.0f; }

        if (glm::length(direction) > 0.0f) {
            direction = glm::normalize(direction);

            if (direction.z > 0.0f) {
                _camera.processKeyboard(FRONT, direction.z * speed);
            } else if (direction.z < 0.0f) {
                _camera.processKeyboard(BACK, -direction.z * speed);
            }

            if (direction.x > 0.0f) {
                _camera.processKeyboard(RIGHT, direction.x * speed);
            } else if (direction.x < 0.0f) {
                _camera.processKeyboard(LEFT, -direction.x * speed);
            }

            if (direction.y > 0.0f) {
                _camera.processKeyboard(UP, direction.y * speed);
            } else if (direction.y < 0.0f) {
                _camera.processKeyboard(DOWN, -direction.y * speed);
            }
        }

        if (_keysMap[KEY_ESC]) {
            glutLeaveMainLoop();
        }
    }

    // LMB, RMB, MMB
    void Input::mouseButtonEvent(int button, int state, int x, int y) {
        if (button == GLUT_RIGHT_BUTTON) {
            if (state == GLUT_DOWN) {
                _keysMap[MOUSE_BUTTON_RIGHT] = true;
            } else if (state == GLUT_UP) {
                _keysMap[MOUSE_BUTTON_RIGHT] = false;
            }
        }
    }

    // mouse movement - changing yaw and pitch
    void Input::mouseMoveEvent(int x, int y) {
        int centerX = _winWidth / 2;
        int centerY = _winHeight / 2;

        if (x == centerX && y == centerY) return;

        float deltaX = static_cast<float>(x - centerX);
        float deltaY = static_cast<float>(centerY - y);

        glutWarpPointer(centerX, centerY);

        if (_firstMouseMovement == false) {
            _firstMouseMovement = true;
            return;
        }

        // if RMB pressed then drag, otherwise move around
        if (_keysMap[MOUSE_BUTTON_RIGHT]) {
            _camera.processMouseDrag(deltaX*MOUSE_DRAG_COEFF, deltaY*MOUSE_DRAG_COEFF);
        } else {
            _camera.processMouseMovement(deltaX, deltaY);
        }

        glutPostRedisplay();
    }

    void Input::mouseWheelEvent(int wheel, int direction, int x, int y) {
        if (direction > 0) {
            _camera.addFov(-3.0f);
        } else {
            _camera.addFov(3.0f);
        }

        glutPostRedisplay();
    }
}
