#include "scene.h"

namespace copakond {
    float Scene::updateTime() {
        int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
        uint64_t prevTime = time;
        time = currentFrameTime;
        return (currentFrameTime - prevTime) / 1000.0f; // delta time
    }

    void Scene::addToScene(Mesh* mesh) {
        meshes.push_back(mesh);

        auto *light = dynamic_cast<Light*>(mesh);
        auto *spline = dynamic_cast<Spline*>(mesh);
        auto *collider = dynamic_cast<CollisionShape*>(mesh);

        if (light) { lights.push_back(light); }
        if (spline) { splines.push_back(spline); }
        if (collider) { colliders.push_back(collider); }
    }
}