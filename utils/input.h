#ifndef PGR_SEM_COPAKOND_INPUT_H
#define PGR_SEM_COPAKOND_INPUT_H

#define IS_SPECIAL_KEY 256

#include "pgr.h"
#include "../geometry/camera.h"

namespace copakond {
    class Input {
    private:
        Camera &camera;
        int WIN_WIDTH;
        int WIN_HEIGHT;
        bool keys_map[512] = {false}; // 256 normal, 256 special

    public:
        Input(Camera &cam, int WIN_WIDTH, int WIN_HEIGHT);

        void update(int WIN_WIDTH, int WIN_HEIGHT);

        void keyboardInputEvent(unsigned char key, int x, int y);
        void specKeyboardInputEvent(int key, int x, int y);
        void keyboardUpInputEvent(unsigned char key, int x, int y);
        void specKeyboardUpInputEvent(int key, int x, int y);

        void keyInput(float deltaTime);
        void mouseMoveEvent(int x, int y);
    };
}

#endif //PGR_SEM_COPAKOND_INPUT_H