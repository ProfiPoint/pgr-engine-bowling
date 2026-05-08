#ifndef PGR_SEM_COPAKOND_INPUTCONTROLLER_H
#define PGR_SEM_COPAKOND_INPUTCONTROLLER_H

#include "controller.h"
#include "../../geometry/camera.h"
#include "../../parser/input.h"
#include "../../animation/spline.h"

namespace copakond {
    class InputController : public Controller {
    private:
        bool _canMove = true;
        bool _isFullScreen = false;

        Camera* camera;
        Input* input;
        Spline* _spline = nullptr;

        void toggleFullScreen();
        void switchCamera(int mode);

    public:
        float baseSpeed = 10.0f;
        float shiftMultiplier = 1.5f;
        float mouseDragCoeff = 0.05f;

        InputController(Camera* cam, Input* input) : camera(cam), input(input) {};

        void update(float deltaTime) override;
        unsigned char raycast(int x, int y);
        void setCameraSpline(Spline *spline) { _spline = spline; }

        void onMouseButtonEvent(int button, int state, int x, int y) override;
        void onSpecialKeyEvent(int key, int x, int y, bool isDown) override;
        void onMenuEvent(int option) override;
    };
}

#endif //PGR_SEM_COPAKOND_INPUTCONTROLLER_H
