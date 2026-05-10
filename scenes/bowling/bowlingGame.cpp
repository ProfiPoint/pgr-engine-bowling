#include "bowlingGame.h"

#include <algorithm>

#include "../../meshes/mesh.h"
#include "../../meshes/collision/rigidSphere.h"
#include "../../geometry/camera.h"

#define DOOR_OPEN_SPEED 0.07f
#define DOOR_MAX_OFFSET 0.45f

namespace copakond {
    void BowlingGame::update(float deltaTime) {
        if (bowlingAlleyOpened1) {
            offsetDoor1 += deltaTime * DOOR_OPEN_SPEED;
            offsetDoor1 = std::min(offsetDoor1, DOOR_MAX_OFFSET);
        } else {
            offsetDoor1 -= deltaTime * DOOR_OPEN_SPEED;
            offsetDoor1 = std::max(offsetDoor1, 0.0f);
        }
        if (bowlingAlleyOpened2) {
            offsetDoor2 += deltaTime * DOOR_OPEN_SPEED;
            offsetDoor2 = std::min(offsetDoor2, DOOR_MAX_OFFSET);
        } else {
            offsetDoor2 -= deltaTime * DOOR_OPEN_SPEED;
            offsetDoor2 = std::max(offsetDoor2, 0.0f);
        }
        if (bowlingAlleyOpened3) {
            offsetDoor3 += deltaTime * DOOR_OPEN_SPEED;
            offsetDoor3 = std::min(offsetDoor3, DOOR_MAX_OFFSET);
        } else {
            offsetDoor3 -= deltaTime * DOOR_OPEN_SPEED;
            offsetDoor3 = std::max(offsetDoor3, 0.0f);
        }
        if (bowlingAlleyOpened4) {
            offsetDoor4 += deltaTime * DOOR_OPEN_SPEED;
            offsetDoor4 = std::min(offsetDoor4, DOOR_MAX_OFFSET);
        } else {
            offsetDoor4 -= deltaTime * DOOR_OPEN_SPEED;
            offsetDoor4 = std::max(offsetDoor4, 0.0f);
        }
        door1->position().y = offsetDoor1;
        door2->position().y = offsetDoor2;
        door3->position().y = offsetDoor3;
        door4->position().y = offsetDoor4;

        // update bowling ball if rolling
        timeToDespawnBowlingBall -= deltaTime;
        if (rollingBowlingBallNow && timeToDespawnBowlingBall <= 0.0f) {
            selectedBowlingBall->show();
            selectedBowlingBall = nullptr;
            rollingBowlingBallNow = false;
            bowlingBall->disable();
            bowlingBall->position() = glm::vec3(0.0f, 1000.0f, 0.0f);
        }
    }

    void BowlingGame::throwBall(float power) {
        if (!selectedBowlingBall) { return; }
        if (rollingBowlingBallNow) { return; }

        bowlingBall->enable();
        rollingBowlingBallNow = true;
        timeToDespawnBowlingBall = 20.0f;

        // set position and velocity of the ball based of the camera position
        glm::vec3 camRot = camera->rotation();

        glm::vec3 lookDirection = glm::vec3(
            cos(camRot.y) * cos(camRot.x),
            sin(camRot.x),
            sin(camRot.y) * cos(camRot.x)
        );
        lookDirection = glm::normalize(lookDirection);

        // add offset to prevnet collision
        float spawnDistanceOffset = 1.0f;
        bowlingBall->position() = camera->position() + (lookDirection * spawnDistanceOffset);
        bowlingBall->velocity() = lookDirection * power;
    }

    void BowlingGame::pickBowlingBall(Mesh* bowlingBall, float power) {
        if (selectedBowlingBall) { throwBall(power); return; }

        selectedBowlingBall = bowlingBall;
        bowlingBall->hide();
    }
}
