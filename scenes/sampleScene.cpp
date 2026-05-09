#include "sampleScene.h"

namespace copakond {
    SampleScene::SampleScene(const char *sceneName, Input* input, Shader* shader, int winWidth, int winHeight): Scene(sceneName, input, shader, winWidth, winHeight) {
        camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 1000.0f);
    }

    SampleScene::~SampleScene() {};


    void SampleScene::init() {
        inputController = new InputController(camera, input);
        LevelEditor* lev = new LevelEditor(this);
        inputController->setLevelEditor(lev);

        std::shared_ptr<Material> teddyMaterial = std::make_shared<Material>(
            glm::vec3(0.5f, 0.33f, 0.2f) * 0.1f,
            glm::vec3(0.5f, 0.33f, 0.2f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            16.0f, 0.5f
        );

        std::shared_ptr<Material> labelMaterial = std::make_shared<Material>(
            glm::vec3(0.5f, 0.33f, 0.2f) * 0.1f,
            glm::vec3(0.5f, 0.33f, 0.2f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            16.0f, 0.5f
        );

        glm::vec3 lightPosition = glm::vec3(-8.0f, 0.0f, 5.0f);
        glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 lightAmbient = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 lightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

        //Light *light = new SpotLight(lightPosition, lightDirection, lightAmbient, lightDiffuse, lightSpecular, 20.0f, 30.0f, 5.0f, false);
        //addToScene(light);
        //Light *light1 = new PointLight(lightPosition, lightAmbient, lightDiffuse, lightSpecular, 50.0f, true);
        //addToScene(light1);
        sun = new DirectionalLight(-lightDirection, lightAmbient, lightDiffuse, glm::vec3(0.0f, 0.0f, 0.0f));
        addToScene(sun);

        //Light *light3 = new DirectionalLight(lightDirection, lightAmbient, lightDiffuse, lightSpecular);
        //addToScene(light3);

        //Mesh* triangleMesh = new Mesh();
        //addToScene(triangleMesh);
        //Mesh *teddyMesh = new ObjMesh("meshes/models/teddy.obj", true);
        //teddyMesh->setMaterial(teddyMaterial);
        //addToScene(teddyMesh);

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

        Mesh *oldShipMesh = new ObjMesh("assets/models/ship.obj", true, glm::vec3(-10.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, -glm::pi<float>()/2, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f));
        oldShipMesh->setMaterial(teddyMaterial);
        addToScene(oldShipMesh);

        Mesh *shipMesh = new ObjMesh("assets/models/ship2.obj", false, glm::vec3(-5.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, glm::pi<float>(), 0.0f), glm::vec3(0.125f, 0.125f, 0.125f));
        addToScene(shipMesh);

        Mesh *bodyMesh = new ObjMesh("assets/models/characters/character-a.obj", false, glm::vec3(0.0f, -1.0f, 0.0f),
                                       glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bodyMesh);

        Mesh *body2Mesh = new ObjMesh("assets/models/characters/character-f.obj", false, glm::vec3(2.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(body2Mesh);

        body2Mesh->setParent(bodyMesh);


        Mesh *flagMesh = new ObjMesh("assets/models/flag.obj", true, glm::vec3(0.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(flagMesh);
        flagMesh->setVertexWave(true);
        shipMesh->setVertexWave(true);

        // collision debug
        Mesh *collisionBox = new CollisionBox(glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f), true);
        addToScene(collisionBox);

        Mesh *collisionBox2 = new CollisionSphere(glm::vec3(3.0f,1.0f,1.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f), true);
        addToScene(collisionBox2);

        RigidBody *rigidBody = new RigidBody(glm::vec3(10.0f,5.0f,1.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f), true);
        rigidBody->velocity() = glm::vec3(0.0f, -100.0f, -70.0f);
        addToScene(rigidBody);


        player = new RigidBody(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        camera->setParent(player);
        inputController->setPlayer(player);
        addToScene(player);


        // testing collisions bouncing
        CollisionBox *cb1 = new CollisionBox(glm::vec3(0.0f,-10.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,22.0f), true);
        addToScene(cb1);
        CollisionBox *cb2 = new CollisionBox(glm::vec3(0.0f,10.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,22.0f), true);
        addToScene(cb2);
        CollisionBox *cb3 = new CollisionBox(glm::vec3(0.0f,0.0f,-10.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,20.0f,1.0f), true);
        addToScene(cb3);
        CollisionBox *cb4 = new CollisionBox(glm::vec3(0.0f,0.0f,10.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,20.0f,1.0f), true);
        addToScene(cb4);
        CollisionSphere *cb5 = new CollisionSphere(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(5.0f,5.0f,5.0f), true);
        addToScene(cb5);

        pivotRot = new CollisionBox(glm::vec3(10.0f,10.0f,0.0f), glm::vec3(5.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f), true);
        cb1->setParent(pivotRot);
        cb2->setParent(pivotRot);
        cb3->setParent(pivotRot);
        cb4->setParent(pivotRot);
        cb5->setParent(pivotRot);



        CollisionBox *cba1 = new CollisionBox(glm::vec3(0.0f,-15.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(20.0f,1.0f,7.0f), true);
        addToScene(cba1);
        CollisionBox *cba2 = new CollisionBox(glm::vec3(-10.0f,-15.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,6.0f,7.0f), true);
        addToScene(cba2);
        CollisionBox *cba3 = new CollisionBox(glm::vec3(10.0f,-15.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,6.0f,7.0f), true);
        addToScene(cba3);
        RigidSphere *rigidBody3 = new RigidSphere(glm::vec3(0.0f,-13.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f), true);
        rigidBody3->velocity() = glm::vec3(30.0f, 0.0f, 0.0f);
        addToScene(rigidBody3);
        flagMesh->setParent(rigidBody3);

        cba1->physicsMaterial.bounciness = 0.98f;
        cba2->physicsMaterial.bounciness = 1.0f;
        cba3->physicsMaterial.bounciness = 1.0f;
        rigidBody3->physicsMaterial.bounciness = 1.0f;

        cba1->physicsMaterial.friction = 0.0f;
        rigidBody3->physicsMaterial.friction = 0.0f;
        rigidBody3->gravity() = glm::vec3(0.0f, -100.0f, 0.0f);




        TextLabel *textLabel1 = new TextLabel("assets/fonts/fredoka-one/fredokaone2.png", labelMaterial);
        textLabel1->scale() = glm::vec3(6.0f,1.0f,1.0f);
        textLabel1->position() = glm::vec3(0.0f, 6.0f, 0.0f);
        textLabel1->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
        textLabel1->setText("Hello World!");
        addToScene(textLabel1);

        TextLabel *textLabel2 = new TextLabel("assets/fonts/fredoka-one/fredokaone2.png");
        textLabel2->scale() = glm::vec3(50.0f,1.0f,1.0f);
        textLabel2->position() = glm::vec3(0.0f, 10.0f, 0.0f);
        textLabel2->setColor(glm::vec3(1.0f, 0.5f, 0.0f));
        textLabel2->setText("copakond Presents super fun project :D 3257 &*@!#$ 131 13 13a1 d3a1wda51d65aww11d65a1d");
        addToScene(textLabel2);

        ImageSequenceLabel *imageSequenceLabel = new ImageSequenceLabel("assets/decals/cara_mia_portal2.jpg", 20, 40*40, 40, 40);
        imageSequenceLabel->position() = glm::vec3(0.0f, 0.0f, -20.0f);
        imageSequenceLabel->scale() = glm::vec3(16*2.0f,9*2.0f,1.0f);
        addToScene(imageSequenceLabel);

        ImageMoving *imageMoving = new ImageMoving("assets/decals/arrow2.png", glm::vec2(0.0f, -1.0f), glm::vec2(1.0f, 8.0f));
        imageMoving->position() = glm::vec3(0.0f, 0.0f, -14.0f);
        imageMoving->scale() = glm::vec3(3.0f, 3*8.0f,1.0f);
        addToScene(imageMoving);


        // clocks
        ImageLabel *clock = new ImageLabel("assets/decals/clock.png");
        clock->position() = glm::vec3(0.0f, 6.0f, 0.1f);
        clock->scale() = glm::vec3(3.0f,3.0f,3.0f);
        addToScene(clock);

        clockHandSec = new ImageLabel("assets/decals/handSeconds2.png");
        clockHandSec->position() = glm::vec3(0.0f, 0.0f, 0.005f);
        clockHandSec->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
        clockHandSec->setParent(clock);
        addToScene(clockHandSec);

        clockHandMin = new ImageLabel("assets/decals/handMinutes2.png");
        clockHandMin->position() = glm::vec3(0.0f, 0.0f, 0.01f);
        clockHandMin->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
        clockHandMin->setParent(clock);
        addToScene(clockHandMin);

        clockHandHour = new ImageLabel("assets/decals/handHours2.png");
        clockHandHour->position() = glm::vec3(0.0f, 0.0f, 0.01f);
        clockHandHour->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
        clockHandHour->setParent(clock);
        addToScene(clockHandHour);

        std::vector<glm::vec3> cameraSplinePoints = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(5.0f, 2.0f, 5.0f),
            glm::vec3(10.0f, 0.0f, 10.0f),
            glm::vec3(15.0f, 5.0f, 0.0f),
            glm::vec3(7.0f, 13.0f, -5.0f),
            glm::vec3(10.0f, 100.0f, 10.0f),
        };

        Spline *cameraSpline = new CatmullRoll(
            20.0f,
            cameraSplinePoints,
            player->position(),
            [this](glm::vec3 derivative) {
                if (glm::length(derivative) > 0.0001f) {  // prevent on screen glitching
                    camera->lookToPoint(camera->getPosition() + derivative);
                }
            }
        );

        addToScene(cameraSpline);
        cameraSpline->pause();
        inputController->setCameraSpline(cameraSpline);


        Fog fog = Fog(30.0f, 50.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        camera->setFog(fog);
    }

    void SampleScene::update(float deltaTime) {
        inputController->update(deltaTime);

        camera->position() = player->getWorldPosition();


        // updating clocks time and hands:
        clockHandHour->rotation() = glm::vec3(0.0f, 0.0f, -clockTime[0]/12*(2*glm::pi<float>()));
        clockHandMin->rotation() = glm::vec3(0.0f, 0.0f, -clockTime[1]/60*(2*glm::pi<float>()));
        clockHandSec->rotation() = glm::vec3(0.0f, 0.0f, -clockTime[2]/60*(2*glm::pi<float>()));

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

    void SampleScene::physics_update(float deltaTime) {
        return;
    }

    void SampleScene::onKeyboardEvent(unsigned char key, int x, int y, bool isDown) {
        if (inputController) {
            inputController->onKeyboardEvent(key, x, y, isDown);
        }
    }

    void SampleScene::onMouseButtonEvent(int button, int state, int x, int y) {
        inputController->onMouseButtonEvent(button, state, x, y);
    }

    void SampleScene::onMouseWheelEvent(int wheel, int direction, int x, int y) {
        if (inputController->getLevelEditor()->getEditMode() == EditMode::NONE) {
            if (direction > 0) {
                camera->addFov(-3.0f);
            } else {
                camera->addFov(3.0f);
            }
        }

        inputController->getLevelEditor()->onMouseWheelEvent(wheel, direction, x, y);
    }

    void SampleScene::onMenuEvent(int option) {
        if (inputController) {
            inputController->onMenuEvent(option);
        }
    }
}
