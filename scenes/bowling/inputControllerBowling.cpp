#include "inputControllerBowling.h"
#include "bowlingScene.h"

namespace copakond {
    void InputControllerBowling::update(float deltaTime) {
        const auto keysMap = input->keysMap;

        // keyboard input
        float currentSpeed = baseSpeed;
        if (input->keysMap[KEY_SHIFT]) { currentSpeed *= shiftMultiplier; }
        float speed = currentSpeed;

        glm::vec3 direction(0.0f);

        if (keysMap['w'] || keysMap[GLUT_KEY_UP + IS_SPECIAL_KEY]) { direction.z += 1.0f; }
        if (keysMap['s'] || keysMap[GLUT_KEY_DOWN + IS_SPECIAL_KEY]) { direction.z -= 1.0f; }
        if (keysMap['a'] || keysMap[GLUT_KEY_LEFT + IS_SPECIAL_KEY]) { direction.x -= 1.0f; }
        if (keysMap['d'] || keysMap[GLUT_KEY_RIGHT + IS_SPECIAL_KEY]) { direction.x += 1.0f; }
        if (keysMap['e']) {
            if (player->isEnabled()) {
                selectBowlingBallE();
            } else {
                direction.y += 1.0f;
            }
        }
        if (keysMap['q']) {
            if (player->isEnabled()) {
                // nothing
            } else {
                direction.y += -1.0f;
            }
        }

        if (glm::length(direction) > 0.0f && _canMove) {
            direction = glm::normalize(direction);

            // moving with rigid body player
            if (glm::length(direction) > 0.0f && _canMove) {
                float yaw = camera->rotation().y;

                glm::vec3 forward = glm::normalize(glm::vec3(cos(yaw), 0.0f, sin(yaw)));
                glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

                glm::vec3 moveVector = (forward * direction.z) + (right * direction.x) + (up * direction.y);

                if (glm::length(moveVector) > 0.0f) {
                    moveVector = glm::normalize(moveVector);
                    if (player->isEnabled()) {
                        player->velocity() = moveVector * speed; // if enabled - update it using velocity (rigid body)
                    } else {
                        player->position() += moveVector * speed * deltaTime; // if disabled update it using positon (normal geometry node)
                    }
                }
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

        if (keysMap[GLUT_KEY_F1 + IS_SPECIAL_KEY]) {
            onMenuEvent(1);
            keysMap[GLUT_KEY_F1 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[GLUT_KEY_F2 + IS_SPECIAL_KEY]) {
            onMenuEvent(2);
            keysMap[GLUT_KEY_F2 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[GLUT_KEY_F3 + IS_SPECIAL_KEY]) {
            onMenuEvent(3);
            keysMap[GLUT_KEY_F3 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[GLUT_KEY_F4 + IS_SPECIAL_KEY]) {
            onMenuEvent(4);
            keysMap[GLUT_KEY_F4 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[GLUT_KEY_F5 + IS_SPECIAL_KEY]) {
            scene->getGame()->toggleDoor1();
            keysMap[GLUT_KEY_F5 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[GLUT_KEY_F6 + IS_SPECIAL_KEY]) {
            scene->getGame()->toggleDoor2();
            keysMap[GLUT_KEY_F6 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[GLUT_KEY_F7 + IS_SPECIAL_KEY]) {
            scene->getGame()->toggleDoor3();
            keysMap[GLUT_KEY_F7 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[GLUT_KEY_F8 + IS_SPECIAL_KEY]) {
            scene->getGame()->toggleDoor4();
            keysMap[GLUT_KEY_F8 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[GLUT_KEY_F11 + IS_SPECIAL_KEY]) {
            onMenuEvent(6);
            keysMap[GLUT_KEY_F11 + IS_SPECIAL_KEY] = false;
        }

        if (keysMap[KEY_ESC]) {
            glutLeaveMainLoop();
            exit(0);
        }
    }

    void InputControllerBowling::onMouseButtonEvent(int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            raycast(x, y);
        }
    }

    void InputControllerBowling::selectBowlingBallE() {
        int raycastResult = raycast(input->_winWidth/2, input->_winHeight/2);
        for (int bowlingBallId : scene->getBowlingBallIds()) {
            if (raycastResult == bowlingBallId) {
                for (Mesh *mesh : scene->getMeshes()) {
                    if (mesh->getId() == bowlingBallId) {
                        scene->getGame()->pickBowlingBall(mesh);
                        return;
                    }
                }
            }
        }

        scene->getGame()->throwBall();
    }

    int InputControllerBowling::raycast(int x, int y) {
        unsigned char objectClickedId = 0;
        glReadPixels(x,  input->_winHeight - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &objectClickedId);
        std::cout << "Raycast clicked at X: " << x << " Y: " << y << " ID: " << (int)objectClickedId << std::endl;

        // connect to the level editor
        _levelEditor->onObjectClickedEvent((int)objectClickedId);

        return (int)objectClickedId;
    }

    void InputControllerBowling::onMenuEvent(int option) {
        if (option >= 1 && option <= 5) {
            switchCamera(option);
        }
        else if (option == 6) {
            toggleFullScreen();
        }
    }

    void InputControllerBowling::switchCamera(int mode) {
        switch(mode) {
            case 1: // player mode
                _canMove = true;
                if (_spline) { _spline->pause(); _spline->reset(); }
                player->enable();
                break;
            case 2: // free cam
                _canMove = true;
                if (_spline) { _spline->pause(); _spline->reset(); }
                player->disable();
                break;
            case 3: // CR spline
                _canMove = false;
                if (_spline) { _spline->unpause(); }
                player->disable();
                break;
            case 4: // pos 1
                _canMove = false;
                if (_spline) { _spline->pause(); }
                player->position() = glm::vec3(5.0f, 0.0f, 20.0f);
                camera->lookToPoint(glm::vec3(0.0f, 0.0f, 0.0f));
                player->disable();
                break;
            case 5: // pos 2
                _canMove = false;
                if (_spline) { _spline->pause(); }
                player->position() = glm::vec3(5.0f, 0.0f, -20.0f);
                camera->lookToPoint(glm::vec3(0.0f, 0.0f, 0.0f));
                player->disable();
                break;
        }
    }

    void InputControllerBowling::toggleFullScreen() {
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

    void InputControllerBowling::onKeyboardEvent(unsigned char key, int x, int y, bool isDown) {
        _levelEditor->onKeyboardEvent(key, x, y, isDown);
    }

}