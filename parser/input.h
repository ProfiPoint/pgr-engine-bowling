#ifndef PGR_SEM_COPAKOND_INPUT_H
#define PGR_SEM_COPAKOND_INPUT_H

#define IS_SPECIAL_KEY 256

#define KEY_ESC 27
#define KEY_BACKSPACE 8
#define KEY_SHIFT 513
#define KEY_SPACE ' '
#define MOUSE_BUTTON_LEFT 514
#define MOUSE_BUTTON_RIGHT 515
#define MOUSE_BUTTON_MIDDLE 516

#include "../pgr-portable.h"
#include "../geometry/camera.h"

namespace copakond {
    class Input {
    public:
        bool keysMap[1024] = {false}; // 256 normal, 256 special
        float mouseDeltaX = 0.0f;
        float mouseDeltaY = 0.0f;

        Camera &_camera;
        int _winWidth;
        int _winHeight;

        bool _firstMouseMovement = false;

        int _windowWidth = 0;
        int _windowHeight = 0;
        int _windowPosX = 0;
        int _windowPosY = 0;

        Input(Camera &cam, int winWidth, int winHeight);

        void screenResize(int winWidth, int winHeight);
        void resetMouseTarget() { _firstMouseMovement = false; }

        void keyboardInputEvent(unsigned char key, int x, int y);
        void specKeyboardInputEvent(int key, int x, int y);
        void keyboardUpInputEvent(unsigned char key, int x, int y);
        void specKeyboardUpInputEvent(int key, int x, int y);

        void mouseButtonEvent(int button, int state, int x, int y);
        void mouseMoveEvent(int x, int y);
        void mouseWheelEvent(int wheel, int direction, int x, int y);
    };
}

#endif //PGR_SEM_COPAKOND_INPUT_H
