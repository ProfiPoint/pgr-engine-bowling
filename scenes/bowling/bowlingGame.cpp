#include "bowlingGame.h"

#include <algorithm>

#include "../../meshes/mesh.h"

#define DOOR_OPEN_SPEED 0.07f
#define DOOR_MAX_OFFSET 0.45f

namespace copakond {
    BowlingGame::BowlingGame() {}
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
    }
}
