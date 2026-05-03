#include "input.h"

#include <iostream>

#include "../animation/spline.h"

#define SHIFT_BOOST 1.5f
#define MOUSE_DRAG_COEFF 0.05f

// TODO move this all into some other script, the logic

namespace copakond {
    Input::Input(Camera &cam, int winWidth, int winHeight) : _camera(cam), _winWidth(winWidth), _winHeight(winHeight) {
    }

    void Input::update(int winWidth, int winHeight) {
        _winWidth = winWidth;
        _winHeight = winHeight;
    }

    // saving input to key map once some key is pressed and unpressed
    void Input::keyboardInputEvent(unsigned char key, int x, int y) {
        keysMap[std::tolower(key)] = true;
        keysMap[std::toupper(key)] = true;

        if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) keysMap[KEY_SHIFT] = true;
    }

    void Input::specKeyboardInputEvent(int key, int x, int y) {
        keysMap[key + IS_SPECIAL_KEY] = true;

        if (keysMap[GLUT_KEY_F1 + IS_SPECIAL_KEY]) {
            _canMove = true;
            _spline->pause();
        }

        if (keysMap[GLUT_KEY_F2 + IS_SPECIAL_KEY]) {
            _canMove = false;
            _spline->reset();
            _spline->unpause();
        }

        if (keysMap[GLUT_KEY_F3 + IS_SPECIAL_KEY]) {
            _canMove = false;
            _spline->pause();
            _camera.position() = glm::vec3(5.0f, 0.0f, 20.0f);
            _camera.lookToPoint(glm::vec3(0.0f, 0.0f, 0.0f));
        }

        if (keysMap[GLUT_KEY_F4 + IS_SPECIAL_KEY]) {
            _canMove = false;
            _spline->pause();
            _camera.position() = glm::vec3(5.0f, 0.0f, -20.0f);
            _camera.lookToPoint(glm::vec3(0.0f, 0.0f, 0.0f));
        }

        if (keysMap[GLUT_KEY_F11 + IS_SPECIAL_KEY]) {
            if (_isFullScreen) {
                glutReshapeWindow(_windowWidth, _windowHeight);
                glutPositionWindow(_windowPosX, _windowPosY);
                _isFullScreen = false;
            } else {
                _windowWidth = glutGet(GLUT_WINDOW_WIDTH);
                _windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
                _windowPosX = glutGet(GLUT_WINDOW_X);
                _windowPosY = glutGet(GLUT_WINDOW_Y);

                glutFullScreen();
                _isFullScreen = true;
            }
        }

        if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) keysMap[KEY_SHIFT] = true;
    }

    void Input::keyboardUpInputEvent(unsigned char key, int x, int y) {
        keysMap[std::tolower(key)] = false;
        keysMap[std::toupper(key)] = false;

        if (!(glutGetModifiers() & GLUT_ACTIVE_SHIFT)) {
            keysMap[KEY_SHIFT] = false;
        }
    }

    void Input::specKeyboardUpInputEvent(int key, int x, int y) {
        keysMap[key + IS_SPECIAL_KEY] = false;

        if (!(glutGetModifiers() & GLUT_ACTIVE_SHIFT)) {
            keysMap[KEY_SHIFT] = false;
        }
    }

    // parsing key movement WASD / arrows
    void Input::keyInput(float deltaTime) {
        if (keysMap[KEY_SHIFT]) { shiftSpeedBoost = SHIFT_BOOST;  } else { shiftSpeedBoost = 1.0f; }
        float speed = deltaTime * shiftSpeedBoost;
        glm::vec3 direction(0.0f);

        if (keysMap['w'] || keysMap[GLUT_KEY_UP + IS_SPECIAL_KEY]) { direction.z += 1.0f; }
        if (keysMap['s'] || keysMap[GLUT_KEY_DOWN + IS_SPECIAL_KEY]) { direction.z -= 1.0f; }
        if (keysMap['a'] || keysMap[GLUT_KEY_LEFT + IS_SPECIAL_KEY]) { direction.x -= 1.0f; }
        if (keysMap['d'] || keysMap[GLUT_KEY_RIGHT + IS_SPECIAL_KEY]) { direction.x += 1.0f; }
        if (keysMap['e']) { direction.y += 1.0f; }
        if (keysMap['q']) { direction.y -= 1.0f; }

        if (glm::length(direction) > 0.0f && _canMove) {
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

        if (keysMap[KEY_ESC]) {
            glutLeaveMainLoop();
        }
    }

    unsigned char Input::raycast(int x, int y) const {
        unsigned char objectClickedId = 0;
        glReadPixels(x, _winHeight - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &objectClickedId);
        return objectClickedId;
    }

    // LMB, RMB, MMB
    unsigned char Input::mouseButtonEvent(int button, int state, int x, int y) {


        if (button == GLUT_MIDDLE_BUTTON) {
            if (state == GLUT_DOWN) {
                keysMap[MOUSE_BUTTON_RIGHT] = true;
            } else if (state == GLUT_UP) {
                keysMap[MOUSE_BUTTON_RIGHT] = false;
            }
        }

        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                return raycast(x, y);
            }
        }

        return 0;
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
        if (keysMap[MOUSE_BUTTON_RIGHT]) {
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

    void Input::setCameraSpline(Spline *spline) {
        _spline = spline;
    }
}
