#ifndef PGR_SEM_COPAKOND_SAMPLE_SCENE_H
#define PGR_SEM_COPAKOND_SAMPLE_SCENE_H

#include "scene.h"

using namespace copakond;

class SampleScene : public Scene {
public:
    SampleScene(const char *sceneName, Input* input, Shader* shader, int winWidth, int winHeight) : Scene(sceneName, input, shader,
        winWidth, winHeight) {}
    ~SampleScene() override;

    void init() override;
    void update(float deltaTime) override;
    void physics_update(float deltaTime) override;

    void onSpecialKeyEvent(int key, int x, int y, bool isDown) override;


};

#endif // PGR_SEM_COPAKOND_SAMPLE_SCENE_H