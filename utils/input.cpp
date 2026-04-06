#include "input.h"

namespace copakond {
    Input::Input(Camera &cam, int WIN_WIDTH, int WIN_HEIGHT) : camera(cam), WIN_WIDTH(WIN_WIDTH), WIN_HEIGHT(WIN_HEIGHT) {}

    void Input::update(int WIN_WIDTH, int WIN_HEIGHT) {
        Input::WIN_WIDTH = WIN_WIDTH;
        Input::WIN_HEIGHT = WIN_HEIGHT;
    }

    // saving input to key map once some key is pressed and unpressed
    void Input::keyboardInputEvent(unsigned char key, int x, int y) {
        keys_map[key] = true;
    }
    void Input::specKeyboardInputEvent(int key, int x, int y) {
        keys_map[key+256] = true;
    }
    void Input::keyboardUpInputEvent(unsigned char key, int x, int y) {
        keys_map[key] = false;
    }
    void Input::specKeyboardUpInputEvent(int key, int x, int y) {
        keys_map[key+256] = false;
    }

    // parsing key movement WASD / arrows
    void Input::keyInput(float deltaTime) {
        if (keys_map['w'] || keys_map['W']) camera.processKeyboard(FRONT, deltaTime);
        if (keys_map['s'] || keys_map['S']) camera.processKeyboard(BACK, deltaTime);
        if (keys_map['a'] || keys_map['A']) camera.processKeyboard(LEFT, deltaTime);
        if (keys_map['d'] || keys_map['D']) camera.processKeyboard(RIGHT, deltaTime);
        if (keys_map[27]) glutLeaveMainLoop(); // ESC
        if (keys_map[GLUT_KEY_UP + IS_SPECIAL_KEY]) camera.processKeyboard(FRONT, deltaTime);
        if (keys_map[GLUT_KEY_DOWN + IS_SPECIAL_KEY]) camera.processKeyboard(BACK, deltaTime);
        if (keys_map[GLUT_KEY_LEFT + IS_SPECIAL_KEY]) camera.processKeyboard(LEFT, deltaTime);
        if (keys_map[GLUT_KEY_RIGHT + IS_SPECIAL_KEY]) camera.processKeyboard(RIGHT, deltaTime);
    }

    // mouse movement - changing yaw and pitch
    void Input::mouseMoveEvent(int x, int y) {
        int centerX = WIN_WIDTH / 2;
        int centerY = WIN_HEIGHT / 2;

        if (x == centerX && y == centerY) return;

        float deltaX = static_cast<float>(x - centerX);
        float deltaY = static_cast<float>(centerY - y);

        camera.processMouseMovement(deltaX, deltaY);

        glutWarpPointer(centerX, centerY);
        glutPostRedisplay();
    }
}