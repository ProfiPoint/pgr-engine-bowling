#include "sampleScene.h"

using namespace copakond;

float clockTime[] = {0,0,0};

ImageLabel *clock = new ImageLabel("assets/decals/clock.png");
clock->position() = glm::vec3(0.0f, 6.0f, 0.1f);
clock->scale() = glm::vec3(3.0f,3.0f,3.0f);
addToScene(clock);

ImageLabel* clockHandSec = new ImageLabel("assets/decals/handSeconds2.png");
clockHandSec->position() = glm::vec3(0.0f, 0.0f, 0.005f);
clockHandSec->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
clockHandSec->setParent(clock);
addToScene(clockHandSec);

ImageLabel* clockHandMin = new ImageLabel("assets/decals/handMinutes2.png");
clockHandMin->position() = glm::vec3(0.0f, 0.0f, 0.01f);
clockHandMin->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
clockHandMin->setParent(clock);
addToScene(clockHandMin);

ImageLabel* clockHandHour = new ImageLabel("assets/decals/handHours2.png");
clockHandHour->position() = glm::vec3(0.0f, 0.0f, 0.01f);
clockHandHour->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
clockHandHour->setParent(clock);
addToScene(clockHandHour);






void SampleScene::init() {
    // todo
}

void SampleScene::update(float deltaTime) {
    // todo
}

void SampleScene::physics_update(float deltaTime) {
    // todo
}




// todo

Mesh* pivotRot = nullptr;
Light *sun;

void handleCameraSwitching(int key);
void updateTimeAndEnvironment(float deltaTime);


