#ifndef PGR_SEM_COPAKOND_INPUTCONTROLLER_H
#define PGR_SEM_COPAKOND_INPUTCONTROLLER_H

#include "controller.h"
#include "../../geometry/camera.h"
#include "../../parser/input.h"
#include "../../animation/spline.h"

namespace copakond {

    class InputController : Controller {
    private:
        Camera* camera;
        Input* input;
        Spline* activeSpline = nullptr;

    public:
        float baseSpeed = 10.0f;
        float shiftMultiplier = 1.5f;
        float mouseDragCoeff = 0.05f;

        InputController(Camera* cam, Input* input) : camera(cam), input(input) {};

        void update(float deltaTime);
        unsigned char raycast(int x, int y);
        void setCameraSpline(Spline *spline);


        void onKeyInput(float deltaTime);
        void onMouseButtonEvent(int button, int state, int x, int y);
        void onMouseMoveEvent(int x, int y);
        void onMouseWheelEvent(int wheel, int direction, int x, int y);
    };
    };
}
#endif //PGR_SEM_COPAKOND_INPUTCONTROLLER_H
