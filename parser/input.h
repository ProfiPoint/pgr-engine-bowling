#ifndef PGR_SEM_COPAKOND_INPUT_H
#define PGR_SEM_COPAKOND_INPUT_H

#define IS_SPECIAL_KEY 256

#define KEY_ESC 27
#define KEY_SHIFT 513
#define MOUSE_BUTTON_LEFT 514
#define MOUSE_BUTTON_RIGHT 515
#define MOUSE_BUTTON_MIDDLE 516

#include "../pgr-portable.h"
#include "../geometry/camera.h"

namespace copakond {
    class Spline;

    class Input {
    public:
        Camera &_camera;
        Spline *_spline = nullptr;
        int _winWidth;
        int _winHeight;
        bool _canMove = true;

        bool _firstMouseMovement = false;
        float shiftSpeedBoost = 1.0f;

        bool _isFullScreen = false;
        int _windowWidth = 0;
        int _windowHeight = 0;
        int _windowPosX = 0;
        int _windowPosY = 0;

        bool keysMap[1024] = {false}; // 256 normal, 256 special

        Input(Camera &cam, int winWidth, int winHeight);

        void update(int winWidth, int winHeight);
        void setCameraSpline(Spline *spline);

        void keyboardInputEvent(unsigned char key, int x, int y);
        void specKeyboardInputEvent(int key, int x, int y);
        void keyboardUpInputEvent(unsigned char key, int x, int y);
        void specKeyboardUpInputEvent(int key, int x, int y);

        void keyInput(float deltaTime);
        unsigned char raycast(int x, int y) const; // returns object id of the given pixel
        unsigned char mouseButtonEvent(int button, int state, int x, int y);
        void mouseMoveEvent(int x, int y);
        void mouseWheelEvent(int wheel, int direction, int x, int y);
    };
}

#endif //PGR_SEM_COPAKOND_INPUT_H
