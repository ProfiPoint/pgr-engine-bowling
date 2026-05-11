#ifndef PGR_SEM_COPAKOND_BOWLINGGAME_H
#define PGR_SEM_COPAKOND_BOWLINGGAME_H

#include "collisionPin.h"
#include <vector>

#define TOTAL_ROUNDS 3

namespace copakond {
    class Camera;
    class RigidSphere;
    class RigidBody;
    class Mesh;
    class TextLabel;
    class ImageSequenceLabel;
    class ImageSequence;
    enum class BowlingVideoEvent { SPLIT, SPARE, STRIKE, MISS };

    class BowlingGame {
    private:
        float timeToDespawnBowlingBall = 0.0f;
        float videoTimeout = 999.0f;
        bool rollingBowlingBallNow = false;

        int score1[TOTAL_ROUNDS*2+1] = {0,0,0,0,0,0,0};
        int score2[TOTAL_ROUNDS*2+1] = {0,0,0,0,0,0,0};
        int score3[TOTAL_ROUNDS*2+1] = {0,0,0,0,0,0,0};
        int score4[TOTAL_ROUNDS*2+1] = {0,0,0,0,0,0,0};

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
        glm::vec3 plrThrowPos = glm::vec3(0.0f);

        int currentSubround[4] = {0, 0, 0, 0};
        float gameOverTimer[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        bool isGameOver[4] = {false, false, false, false};

        int getClosestAlleyToBowlingBall();
        int resetBowlingBall(); // also returning the number of pins down
        bool checkIfBowlingBallHitTheWall() const;
        void renderText(int alley);
        void playVideo(BowlingVideoEvent event, int alley);

        void evaluateScore(int alley, int pinsKnocked);
        void resetPinsForAlley(int alley);
        void resetGameForAlley(int alley);


    public:
        BowlingGame(Camera *camera) : camera(camera) {};
        void update(float deltaTime);

        void pickBowlingBall(Mesh* bowlingBall, float power = 2.0f);
        void throwBall(float power = 2.0f);

        void toggleDoor1();
        void toggleDoor2();
        void toggleDoor3();
        void toggleDoor4();

        RigidBody *player = nullptr;

        Mesh *door1 = nullptr;
        Mesh *door2 = nullptr;
        Mesh *door3 = nullptr;
        Mesh *door4 = nullptr;

        std::vector<CollisionPin*> pins;
        RigidSphere *bowlingBall = nullptr;

        TextLabel *scoreLabel1;
        TextLabel *scoreLabel2;
        TextLabel *scoreLabel3;
        TextLabel *scoreLabel4;

        ImageSequenceLabel *videoSplit1;
        ImageSequenceLabel *videoSpare2;
        ImageSequenceLabel *videoStrike3;
        ImageSequenceLabel *videoMiss4;

        ImageSequenceLabel *videoIdle1;
        ImageSequenceLabel *videoIdle2;
        ImageSequenceLabel *videoIdle3;
        ImageSequenceLabel *videoIdle4;
    };
}

#endif //PGR_SEM_COPAKOND_BOWLINGGAME_H
