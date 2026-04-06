#include "input.h"

namespace copakond {
    Input::Input(Camera& cam, int WIN_WIDTH, int WIN_HEIGHT) : camera(cam), WIN_WIDTH(WIN_WIDTH), WIN_HEIGHT(WIN_HEIGHT) {}

    void Input::specKeyboardInputEvent(int key, int x, int y) {
        //float deltaTime = glutGet(GLUT_ELAPSED_TIME);
        float deltaTime = 0.1;

        switch (key) {
            case GLUT_KEY_UP:
                camera.processKeyboard(FRONT, deltaTime); break;
            case GLUT_KEY_DOWN:
                camera.processKeyboard(BACK, deltaTime); break;
            case GLUT_KEY_LEFT:
                camera.processKeyboard(LEFT, deltaTime); break;
            case GLUT_KEY_RIGHT:
                camera.processKeyboard(RIGHT, deltaTime); break;
        }

        glutPostRedisplay();
    }

    void Input::keyboardInputEvent(unsigned char key, int x, int y) {
        //float deltaTime = glutGet(GLUT_ELAPSED_TIME);
        float deltaTime = 0.1;

        switch (key) {
            case 'w': case 'W':
                camera.processKeyboard(FRONT, deltaTime); break;
            case 's': case 'S':
                camera.processKeyboard(BACK, deltaTime); break;
            case 'a': case 'A':
                camera.processKeyboard(LEFT, deltaTime); break;
            case 'd': case 'D':
                camera.processKeyboard(RIGHT, deltaTime); break;
            case 27: // ESC
                glutLeaveMainLoop(); break;
        }

        glutPostRedisplay();
    }

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