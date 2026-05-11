#ifndef PGR_SEM_COPAKOND_SCENE_H
#define PGR_SEM_COPAKOND_SCENE_H

#include <iostream>
#include <algorithm>
#include "../pgr-portable.h"
#include "../meshes/mesh.h"
#include "../meshes/model/objMesh.h"
#include "../meshes/label/textLabel.h"
#include "../meshes/label/imageSequenceLabel.h"
#include "../geometry/camera.h"
#include "../light/light.h"
#include "../parser/input.h"
#include "../shaders/shader.h"
#include "../animation/spline.h"
#include "../animation/catmullroll.h"
#include "../animation/bezier.h"
#include "../meshes/collision/collisionBox.h"
#include "../meshes/collision/collisionSphere.h"
#include "../meshes/collision/rigidBody.h"
#include "../meshes/collision/rigidSphere.h"
#include "../meshes/label/imageLabel.h"
#include "../meshes/label/imageMoving.h"
#include "../meshes/model/skybox.h"

namespace copakond {
    /** @brief Determines which objects are written to the stencil buffer for mouse picking */
    enum class StencilSelect { ALL, MESHES, COLLISION };
    extern StencilSelect stencilMode; // only declare once

    /** @brief Base class for all game scenes, managing lifecycle, rendering, and scene entities */
    class Scene {
    protected:
        const char *WIN_TITLE;
        Input* input;
        Shader* shader;

        Camera *camera;
        std::vector<Mesh*> meshes = std::vector<Mesh*>();
        std::vector<Light*> lights = std::vector<Light*>();
        std::vector<Spline*> splines = std::vector<Spline*>();
        std::vector<CollisionShape*> colliders = std::vector<CollisionShape*>();

        Light* sun = nullptr;
        Skybox* skybox = nullptr;

        uint64_t time = 0;
        int winWidth = 0;
        int winHeight = 0;
        float skyboxBlendingCoeff = 0.0f;

        void addToScene(Mesh* mesh);
        void addToScene(Light* light);
        void addToScene(Spline* spline);

    public:
        Scene(const char *sceneName, Input* engineInput, Shader* engineShader, int winWidth, int winHeight) : input(engineInput), shader
        (engineShader), winWidth(winWidth), winHeight(winHeight) {
            WIN_TITLE = sceneName;
            camera = new Camera(glm::vec3(0.0f),glm::vec3(0.0f), 1000.0f); // sample camera
        }

        virtual ~Scene() = default;

        // getters for main
        const std::vector<Mesh*>& getMeshes() const { return meshes; }
        const std::vector<Light*>& getLights() const { return lights; }
        const std::vector<Spline*>& getSplines() const { return splines; }
        const std::vector<CollisionShape*>& getColliders() const { return colliders; }
        Skybox* getSkybox() const { return skybox; }
        Light* getSun() const { return sun; }
        Camera& getCamera() { return *camera; }
        Shader* getShader() const { return shader; }
        Input* getInput() const { return input; }

        /** @brief Calculates delta time since the last frame */
        float updateTime();
        float getSkyboxBlendingCoeff() { return skyboxBlendingCoeff; } // each scene can overwrite it with custom logic
        const char* getSceneName() { return WIN_TITLE; }

        // functions for scene
        virtual void init() {};
        virtual void update(float deltaTime) {};

        /** @brief Fixed-step physics update loop for resolving collisions and forces */
        virtual void physics_update(float deltaTime) {};

        virtual void onKeyboardEvent(unsigned char key, int x, int y, bool isDown) {}

        virtual void onMouseButtonEvent(int button, int state, int x, int y) {}
        virtual void onMouseWheelEvent(int wheel, int direction, int x, int y) {}
        virtual void onMouseMoveEvent(int x, int y) {}

        /** @brief Handles viewport and projection matrix updates on window resize */
        virtual void onScreenResizeEvent(int width, int height) {}

        virtual void onMenuEvent(int option) {}
    };
}

#endif // PGR_SEM_COPAKOND_SCENE_H
