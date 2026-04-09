#ifndef PGR_SEM_COPAKOND_INPUT_H
#define PGR_SEM_COPAKOND_INPUT_H

#define IS_SPECIAL_KEY 256

#include "pgr.h"
#include "../geometry/camera.h"

namespace copakond {
    class Input {
    private:
        Camera &_camera;
        int _winWidth;
        int _winHeight;
        bool _keysMap[512] = {false}; // 256 normal, 256 special

    public:
        Input(Camera &cam, int winWidth, int winHeight);

        void update(int winWidth, int winHeight);

        void keyboardInputEvent(unsigned char key, int x, int y);
        void specKeyboardInputEvent(int key, int x, int y);
        void keyboardUpInputEvent(unsigned char key, int x, int y);
        void specKeyboardUpInputEvent(int key, int x, int y);

        void keyInput(float deltaTime);
        void mouseMoveEvent(int x, int y);
    };
}

#endif //PGR_SEM_COPAKOND_INPUT_H