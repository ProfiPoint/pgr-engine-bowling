#ifndef PGR_SEM_COPAKOND_INPUTCONTROLLERBOWLING_H
#define PGR_SEM_COPAKOND_INPUTCONTROLLERBOWLING_H

#include "../utils/controller.h"
#include "../../geometry/camera.h"
#include "../../parser/input.h"
#include "../../animation/spline.h"
#include "../../meshes/collision/rigidBody.h"
#include "../utils/levelEditor.h"

namespace copakond {
    class BowlingScene;

    class InputControllerBowling : public Controller {
    private:
        bool _canMove = true;
        bool _isFullScreen = false;

        BowlingScene *scene;
        LevelEditor* _levelEditor = nullptr;
        Camera* camera;
        Input* input;
        Spline* _spline = nullptr;
        RigidBody* player = nullptr;
        float spacePower = 2.0f;

        void toggleFullScreen();
        void switchCamera(int mode);

    public:
        float baseSpeed = 1.5f;
        float shiftMultiplier = 1.75f;
        float mouseDragCoeff = 0.05f;

        InputControllerBowling(Camera* cam, Input* input, BowlingScene* scene) : camera(cam), input(input), scene(scene) {};
        void setPlayer(RigidBody* p) { player = p; }
        void setLevelEditor(LevelEditor* lev) { _levelEditor = lev; }
        LevelEditor* getLevelEditor() { return _levelEditor; }

        void update(float deltaTime) override;
        int raycast(int x, int y);
        void setCameraSpline(Spline *spline) { _spline = spline; }

        void selectBowlingBallE();
        void onKeyboardEvent(unsigned char key, int x, int y, bool isDown) override;
        void onMouseButtonEvent(int button, int state, int x, int y) override;
        void onMenuEvent(int option) override;
    };
}

#endif //PGR_SEM_COPAKOND_INPUTCONTROLLERBOWLING_H
