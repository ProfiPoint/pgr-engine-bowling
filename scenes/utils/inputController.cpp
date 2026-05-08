#include "inputController.h"

namespace copakond {
    void InputController::update(float deltaTime) {
        const auto keysMap = input->keysMap;

        // keyboard input
        float currentSpeed = baseSpeed;
        if (input->keysMap[KEY_SHIFT]) { currentSpeed *= shiftMultiplier; }
        float speed = deltaTime * shiftMultiplier;

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
                camera->processKeyboard(FRONT, direction.z * speed);
            } else if (direction.z < 0.0f) {
                camera->processKeyboard(BACK, -direction.z * speed);
            }

            if (direction.x > 0.0f) {
                camera->processKeyboard(RIGHT, direction.x * speed);
            } else if (direction.x < 0.0f) {
                camera->processKeyboard(LEFT, -direction.x * speed);
            }

            if (direction.y > 0.0f) {
                camera->processKeyboard(UP, direction.y * speed);
            } else if (direction.y < 0.0f) {
                camera->processKeyboard(DOWN, -direction.y * speed);
            }
        }

        // mouse movement
        if (input->keysMap[MOUSE_BUTTON_RIGHT]) {
            camera->processMouseDrag(input->mouseDeltaX * mouseDragCoeff, input->mouseDeltaY * mouseDragCoeff);
        } else {
            camera->processMouseMovement(input->mouseDeltaX, input->mouseDeltaY);
        }

        input->mouseDeltaX = 0.0f;
        input->mouseDeltaY = 0.0f;

        if (keysMap[KEY_ESC]) {
            glutLeaveMainLoop();
        }
    }

    void InputController::onMouseButtonEvent(int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            raycast(x, y);
        }
    }

    void InputController::onSpecialKeyEvent(int key, int x, int y, bool isDown) {
        if (!isDown) return; // Only execute on key PRESS, not release

        const auto keysMap = input->keysMap;

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
            camera->position() = glm::vec3(5.0f, 0.0f, 20.0f);
            camera->lookToPoint(glm::vec3(0.0f, 0.0f, 0.0f));
        }

        if (keysMap[GLUT_KEY_F4 + IS_SPECIAL_KEY]) {
            _canMove = false;
            _spline->pause();
            camera->position() = glm::vec3(5.0f, 0.0f, -20.0f);
            camera->lookToPoint(glm::vec3(0.0f, 0.0f, 0.0f));
        }

        if (keysMap[GLUT_KEY_F11 + IS_SPECIAL_KEY]) {
            if (_isFullScreen) {
                glutReshapeWindow(input->_windowWidth, input->_windowHeight);
                glutPositionWindow(input->_windowPosX, input->_windowPosY);
                _isFullScreen = false;
            } else {
                input->_windowWidth = glutGet(GLUT_WINDOW_WIDTH);
                input->_windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
                input->_windowPosX = glutGet(GLUT_WINDOW_X);
                input->_windowPosY = glutGet(GLUT_WINDOW_Y);

                glutFullScreen();
                _isFullScreen = true;
            }
        }
    }

    unsigned char InputController::raycast(int x, int y) {
        std::cout << "Raycast clicked at X: " << x << " Y: " << y << std::endl;
        return 0;
    }
}