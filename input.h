#ifndef PGR_SEM_COPAKOND_INPUT_H
#define PGR_SEM_COPAKOND_INPUT_H

#include "pgr.h"
#include "camera.h"

namespace copakond {
    class Input {
    private:
        Camera& camera;
        int WIN_WIDTH;
        int WIN_HEIGHT;

    public:
        Input(Camera& cam, int WIN_WIDTH, int WIN_HEIGHT);

        void update(int WIN_WIDTH, int WIN_HEIGHT);
        void keyboardInputEvent(unsigned char key, int x, int y);
        void specKeyboardInputEvent(int key, int x, int y);
        void mouseMoveEvent(int x, int y);
    };
}

#endif //PGR_SEM_COPAKOND_INPUT_H