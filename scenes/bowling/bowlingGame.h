#ifndef PGR_SEM_COPAKOND_BOWLINGGAME_H
#define PGR_SEM_COPAKOND_BOWLINGGAME_H

#include "collisionPin.h"
#include <vector>

namespace copakond {
    class Camera;
    class RigidSphere;
    class RigidBody;
    class Mesh;

    class BowlingGame {
    private:
        float timeToDespawnBowlingBall = 0.0f;
        bool rollingBowlingBallNow = false;

        int totalScore1 = 0;
        int totalScore2 = 0;
        int totalScore3 = 0;
        int totalScore4 = 0;

        bool bowlingAlleyOpened1 = false;
        bool bowlingAlleyOpened2 = false;
        bool bowlingAlleyOpened3 = false;
        bool bowlingAlleyOpened4 = false;

        float offsetDoor1 = 0.0f;
        float offsetDoor2 = 0.0f;
        float offsetDoor3 = 0.0f;
        float offsetDoor4 = 0.0f;

        bool canBeUsed1 = true;
        bool canBeUsed2 = true;
        bool canBeUsed3 = true;
        bool canBeUsed4 = true;

        Mesh *selectedBowlingBall = nullptr;
        Camera *camera;

        int getClosestAlleyToBowlingBall();
        int resetBowlingBall(); // also returning the number of pins down
        bool checkIfBowlingBallHitTheWall() const;

    public:
        BowlingGame(Camera *camera) : camera(camera) {};
        void update(float deltaTime);

        void pickBowlingBall(Mesh* bowlingBall, float power = 2.0f);
        void throwBall(float power = 2.0f);

        void toggleDoor1() { bowlingAlleyOpened1 = !bowlingAlleyOpened1; }
        void toggleDoor2() { bowlingAlleyOpened2 = !bowlingAlleyOpened2; }
        void toggleDoor3() { bowlingAlleyOpened3 = !bowlingAlleyOpened3; }
        void toggleDoor4() { bowlingAlleyOpened4 = !bowlingAlleyOpened4; }

        Mesh *door1 = nullptr;
        Mesh *door2 = nullptr;
        Mesh *door3 = nullptr;
        Mesh *door4 = nullptr;

        std::vector<CollisionPin*> pins;
        RigidSphere *bowlingBall = nullptr;
    };
}

#endif //PGR_SEM_COPAKOND_BOWLINGGAME_H
