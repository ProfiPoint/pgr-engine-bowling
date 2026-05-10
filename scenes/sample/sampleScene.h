#ifndef PGR_SEM_COPAKOND_SAMPLE_SCENE_H
#define PGR_SEM_COPAKOND_SAMPLE_SCENE_H

#include "../scene.h"
#include "../utils/inputController.h"

namespace copakond {
    class SampleScene : public Scene {
    private:
        InputController* inputController = nullptr;

        ImageLabel* clock = nullptr;
        ImageLabel* clockHandSec = nullptr;
        ImageLabel* clockHandMin = nullptr;
        ImageLabel* clockHandHour = nullptr;
        Mesh *pivotRot = nullptr;
        RigidBody *player = nullptr;

        float clockTime[3] = {0, 0, 0}; // hh:mm:ss

    public:
        SampleScene(const char *sceneName, Input* input, Shader* shader, int winWidth, int winHeight);
        ~SampleScene() override;

        void init() override;
        void update(float deltaTime) override;
        void physics_update(float deltaTime) override;

        void onMouseButtonEvent(int button, int state, int x, int y) override;
        void onMenuEvent(int option) override;
        void onMouseWheelEvent(int wheel, int direction, int x, int y)  override;
        void onKeyboardEvent(unsigned char key, int x, int y, bool isDown) override;
    };
}

#endif // PGR_SEM_COPAKOND_SAMPLE_SCENE_H