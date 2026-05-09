#include "templateScene.h"

namespace copakond {
    TemplateScene::TemplateScene(const char *sceneName, Input* input, Shader* shader, int winWidth, int winHeight): Scene(sceneName, input, shader, winWidth, winHeight) {
        camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 1000.0f);
    }

    TemplateScene::~TemplateScene() {};


    void TemplateScene::init() {
        inputController = new InputController(camera, input);
        LevelEditor* lev = new LevelEditor(this);
        inputController->setLevelEditor(lev);

        sun = new DirectionalLight(-glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        addToScene(sun);

        skybox = new Skybox(
            "assets/skybox/day/px.png",
            "assets/skybox/day/nx.png",
            "assets/skybox/day/ny.png",
            "assets/skybox/day/py.png",
            "assets/skybox/day/pz.png",
            "assets/skybox/day/nz.png",

            "assets/skybox/night/px2.png",
            "assets/skybox/night/nx2.png",
            "assets/skybox/night/ny2.png",
            "assets/skybox/night/py2.png",
            "assets/skybox/night/pz2.png",
            "assets/skybox/night/nz2.png",

            "shaders/shaders/skybox.vert",
            "shaders/shaders/skybox.frag"
        );

        player = new RigidBody(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        player->disable();
        camera->setParent(player);
        inputController->setPlayer(player);
        addToScene(player);

        Fog fog = Fog(30.0f, 50.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        camera->setFog(fog);
    }

    void TemplateScene::update(float deltaTime) {
        inputController->update(deltaTime);

        camera->position() = player->getWorldPosition();

        clockTime[2] += 600.0f * deltaTime; // smooth seconds
        clockTime[0] += 600.0f * deltaTime / 3600.0f; // smooth hours

        if (clockTime[2] >= 60.0f) {
            clockTime[2] -= 60.0f;
            clockTime[1] += 1.0f;

            if (clockTime[1] >= 60.0f) {
                clockTime[1] -= 60.0f;
            }
        }

        if (clockTime[0] >= 24.0f) {
            clockTime[0] -= 24.0f;
        }

        // update skybox, directional light,
        // skybox day night blending
        float currentHour = clockTime[0];
        skyboxBlendingCoeff = 0.0f; // default day

        if (currentHour >= 20.0f || currentHour <= 4.0f) { skyboxBlendingCoeff = 1.0f; } // full night
        else if (currentHour > 4.0f && currentHour < 8.0f) { skyboxBlendingCoeff = 1.0f - ((currentHour - 4.0f) / 4.0f); } // night -> day
        else if (currentHour > 16.0f && currentHour < 20.0f) { skyboxBlendingCoeff = (currentHour - 16.0f) / 4.0f; } // day -> night

        // update sunlight based of the time
        // z stars at -1, middle 0, end 1 (pi/2, pi, 3pi/2)
        // y stars at 0, middle 1, end 0 (pi/2, pi, 3pi/2)
        float thetaSun = (2 * glm::pi<float>() * currentHour / 24.0f); // 0 is down, 12 is up, 24 down, 6 start, 18 end
        sun->diffuse() = glm::vec3(0.5f, 0.5f, 0.5f) * (1-skyboxBlendingCoeff); // set the intensity
        sun->direction() = glm::vec3(0.0f, glm::cos(thetaSun), glm::sin(thetaSun));
    }

    void TemplateScene::physics_update(float deltaTime) {
        return;
    }

    void TemplateScene::onKeyboardEvent(unsigned char key, int x, int y, bool isDown) {
        if (inputController) {
            inputController->onKeyboardEvent(key, x, y, isDown);
        }
    }

    void TemplateScene::onMouseButtonEvent(int button, int state, int x, int y) {
        inputController->onMouseButtonEvent(button, state, x, y);
    }

    void TemplateScene::onMouseWheelEvent(int wheel, int direction, int x, int y) {
        if (inputController->getLevelEditor()->getEditMode() == EditMode::NONE) {
            if (direction > 0) {
                camera->addFov(-3.0f);
            } else {
                camera->addFov(3.0f);
            }
        }

        inputController->getLevelEditor()->onMouseWheelEvent(wheel, direction, x, y);
    }

    void TemplateScene::onMenuEvent(int option) {
        return;
    }
}
