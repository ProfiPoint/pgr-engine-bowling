#ifndef PGR_SEM_COPAKOND_SAMPLE_SCENE_H
#define PGR_SEM_COPAKOND_SAMPLE_SCENE_H

#include "scene.h"

namespace copakond {
    class SampleScene : public Scene {
    private:
        ImageLabel* clock = nullptr;
        ImageLabel* clockHandSec = nullptr;
        ImageLabel* clockHandMin = nullptr;
        ImageLabel* clockHandHour = nullptr;
        Mesh *pivotRot = nullptr;

        float clockTime[3] = {0, 0, 0}; // hh:mm:ss

    public:
        SampleScene(const char *sceneName, Input* input, Shader* shader, int winWidth, int winHeight);
        ~SampleScene() override;

        void init() override;
        void update(float deltaTime) override;
        void physics_update(float deltaTime) override;
    };
}

#endif // PGR_SEM_COPAKOND_SAMPLE_SCENE_H