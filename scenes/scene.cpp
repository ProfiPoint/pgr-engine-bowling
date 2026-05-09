#include "scene.h"

namespace copakond {
    StencilSelect stencilMode = StencilSelect::ALL;

    float Scene::updateTime() {
        int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
        uint64_t prevTime = time;
        time = currentFrameTime;
        return (currentFrameTime - prevTime) / 1000.0f; // delta time
    }

    void Scene::addToScene(Mesh* mesh) {
        auto *collider = dynamic_cast<CollisionShape*>(mesh);
        if (collider) { colliders.push_back(collider); }

        meshes.push_back(mesh);
    }

    void Scene::addToScene(Light* light) {
        lights.push_back(light);
    }

    void Scene::addToScene(Spline* spline) {
        splines.push_back(spline);
    }
}