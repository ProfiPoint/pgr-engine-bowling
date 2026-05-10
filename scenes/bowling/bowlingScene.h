#ifndef PGR_SEM_COPAKOND_BOWLINGSCENE_H
#define PGR_SEM_COPAKOND_BOWLINGSCENE_H

#include "../scene.h"
#include "bowlingGame.h"
#include "../bowling/inputControllerBowling.h"

namespace copakond {
    class InputControllerBowling;
    class RigidBody;

    class BowlingScene : public Scene {
    private:
        BowlingGame *game;
        InputControllerBowling* inputController = nullptr;
        RigidBody *player = nullptr;

        float clockTime[3] = {0, 0, 0}; // hh:mm:ss
        std::vector<int> bowlingBallIds = {};

    public:
        BowlingScene(const char *sceneName, Input* input, Shader* shader, int winWidth, int winHeight);
        ~BowlingScene() override;

        void init() override;
        void update(float deltaTime) override;
        void physics_update(float deltaTime) override;

        void onMouseButtonEvent(int button, int state, int x, int y) override;
        void onMenuEvent(int option) override;
        void onMouseWheelEvent(int wheel, int direction, int x, int y)  override;
        void onKeyboardEvent(unsigned char key, int x, int y, bool isDown) override;

        BowlingGame *getGame() { return game; }
        std::vector<int> getBowlingBallIds() { return bowlingBallIds; }
    };
}

#endif //PGR_SEM_COPAKOND_BOWLINGSCENE_H
