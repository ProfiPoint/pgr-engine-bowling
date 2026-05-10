#ifndef PGR_SEM_COPAKOND_INPUTCONTROLLER_H
#define PGR_SEM_COPAKOND_INPUTCONTROLLER_H

#include "controller.h"
#include "../../geometry/camera.h"
#include "../../parser/input.h"
#include "../../animation/spline.h"
#include "../../meshes/collision/rigidBody.h"
#include "levelEditor.h"

namespace copakond {

    class InputController : public Controller {
    private:
        bool _canMove = true;
        bool _isFullScreen = false;

        LevelEditor* _levelEditor = nullptr;
        Camera* camera;
        Input* input;
        Spline* _spline = nullptr;
        RigidBody* player = nullptr;

        void toggleFullScreen();
        void switchCamera(int mode);

    public:
        float baseSpeed = 1.5f;
        float shiftMultiplier = 1.75f;
        float mouseDragCoeff = 0.05f;

        InputController(Camera* cam, Input* input) : camera(cam), input(input) {};
        void setPlayer(RigidBody* p) { player = p; }
        void setLevelEditor(LevelEditor* lev) { _levelEditor = lev; }
        LevelEditor* getLevelEditor() { return _levelEditor; }

        void update(float deltaTime) override;
        int raycast(int x, int y);
        void setCameraSpline(Spline *spline) { _spline = spline; }

        void onKeyboardEvent(unsigned char key, int x, int y, bool isDown) override;
        void onMouseButtonEvent(int button, int state, int x, int y) override;
        void onMenuEvent(int option) override;
    };
}

#endif //PGR_SEM_COPAKOND_INPUTCONTROLLER_H
