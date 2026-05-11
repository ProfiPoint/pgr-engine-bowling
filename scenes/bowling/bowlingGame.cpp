#include "bowlingGame.h"

#include <algorithm>

#include "../../meshes/mesh.h"
#include "../../meshes/collision/rigidSphere.h"
#include "../../geometry/camera.h"

#define DOOR_OPEN_SPEED 0.07f
#define DOOR_MAX_OFFSET 0.45f
#define BALL_DESPAWN_TIME 30.0f
#define BALL_MIN_SPEED -0.5f

namespace copakond {
    int BowlingGame::getClosestAlleyToBowlingBall() {
        float dist1 = glm::distance(bowlingBall->position(), door1->position());
        float dist2 = glm::distance(bowlingBall->position(), door2->position());
        float dist3 = glm::distance(bowlingBall->position(), door3->position());
        float dist4 = glm::distance(bowlingBall->position(), door4->position());

        if (dist1 < dist2 && dist1 < dist3 && dist1 < dist4) { return 1; }
        if (dist2 < dist3 && dist2 < dist4) { return 2; }
        if (dist3 < dist4) { return 3; }
        return 4;
    }

    int BowlingGame::resetBowlingBall() {
        // reset bowling ball
        selectedBowlingBall->show();
        selectedBowlingBall = nullptr;
        rollingBowlingBallNow = false;
        bowlingBall->disable();
        bowlingBall->position() = glm::vec3(0.0f, 1000.0f, 0.0f);

        // count and reset all pins
        int count = 0;
        for (CollisionPin *pin : pins) {
            if (pin->isDown()) { ++count; }
            pin->reset();
        }
        return count;
    }

    bool BowlingGame::checkIfBowlingBallHitTheWall() const {
        return bowlingBall->position().x < -11.5f; // if its behind the start of the last wall retrun true
    }


    void BowlingGame::update(float deltaTime) {
        // door opening logic
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
            resetBowlingBall();
        }

        // make sure the ball keeps moving constantly
        if (bowlingBall->velocity().x > BALL_MIN_SPEED) {
            bowlingBall->velocity().x += BALL_MIN_SPEED / 15;
        }

        // if it touches the wall, then end it 5 seconds, instead of waiting 20 seconds to despawn
        if (checkIfBowlingBallHitTheWall()) { timeToDespawnBowlingBall = glm::min(timeToDespawnBowlingBall, 5.0f); }
    }

    void BowlingGame::throwBall(float power) {
        if (!selectedBowlingBall) { return; }
        if (rollingBowlingBallNow) { return; }

        bowlingBall->enable();
        rollingBowlingBallNow = true;
        timeToDespawnBowlingBall = BALL_DESPAWN_TIME;

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
