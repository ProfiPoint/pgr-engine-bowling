#include "input.h"

namespace copakond {
    Input::Input(Camera &cam, int winWidth, int winHeight) : _camera(cam), _winWidth(winWidth), _winHeight(winHeight) {}

    void Input::update(int winWidth, int winHeight) {
        _winWidth = winWidth;
        _winHeight = winHeight;
    }

    // saving input to key map once some key is pressed and unpressed
    void Input::keyboardInputEvent(unsigned char key, int x, int y) {
        _keysMap[std::tolower(key)] = true;
        _keysMap[std::toupper(key)] = true;
    }
    void Input::specKeyboardInputEvent(int key, int x, int y) {
        _keysMap[key+256] = true;
    }
    void Input::keyboardUpInputEvent(unsigned char key, int x, int y) {
        _keysMap[std::tolower(key)] = false;
        _keysMap[std::toupper(key)] = false;
    }
    void Input::specKeyboardUpInputEvent(int key, int x, int y) {
        _keysMap[key+256] = false;
    }

    // parsing key movement WASD / arrows
    void Input::keyInput(float deltaTime) {
        if (_keysMap['w']) _camera.processKeyboard(FRONT, deltaTime);
        if (_keysMap['s']) _camera.processKeyboard(BACK, deltaTime);
        if (_keysMap['a']) _camera.processKeyboard(LEFT, deltaTime);
        if (_keysMap['d']) _camera.processKeyboard(RIGHT, deltaTime);
        if (_keysMap[27]) glutLeaveMainLoop(); // ESC
        if (_keysMap[GLUT_KEY_UP + IS_SPECIAL_KEY]) _camera.processKeyboard(FRONT, deltaTime);
        if (_keysMap[GLUT_KEY_DOWN + IS_SPECIAL_KEY]) _camera.processKeyboard(BACK, deltaTime);
        if (_keysMap[GLUT_KEY_LEFT + IS_SPECIAL_KEY]) _camera.processKeyboard(LEFT, deltaTime);
        if (_keysMap[GLUT_KEY_RIGHT + IS_SPECIAL_KEY]) _camera.processKeyboard(RIGHT, deltaTime);
    }

    // mouse movement - changing yaw and pitch
    void Input::mouseMoveEvent(int x, int y) {
        int centerX = _winWidth / 2;
        int centerY = _winHeight / 2;

        if (x == centerX && y == centerY) return;

        float deltaX = static_cast<float>(x - centerX);
        float deltaY = static_cast<float>(centerY - y);

        _camera.processMouseMovement(deltaX, deltaY);

        glutWarpPointer(centerX, centerY);
        glutPostRedisplay();
    }
}