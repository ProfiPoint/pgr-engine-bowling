#include "bowlingScene.h"
#include "../bowling/inputControllerBowling.h"
#define ALLEY_SPACING 1.8f

namespace copakond {
    BowlingScene::BowlingScene(const char *sceneName, Input* input, Shader* shader, int winWidth, int winHeight): Scene(sceneName, input, shader, winWidth, winHeight) {
        camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 1000.0f);
    }

    BowlingScene::~BowlingScene() {};

    void BowlingScene::init() {
        inputController = new InputControllerBowling(camera, input, this);
        game = new BowlingGame(camera);
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

        player = new RigidBody(glm::vec3(10.0f, 1.25f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f/4, 1.5f, 1.0f/4));
        camera->setParent(player);
        inputController->setPlayer(player);
        game->player = player;
        addToScene(player);

        Fog fog = Fog(30.0f, 50.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        camera->setFog(fog);

        
        //Mesh *bomb = new ObjMesh("assets/models/custom/bomb.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
         //   glm::vec3(1.0f, 1.0f, 1.0f));
        //addToScene(bomb);

        //Mesh *bomb = new ObjMesh("assets/models/custom/trophy.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        //addToScene(bomb);

        // pins
        std::vector<Mesh *> pinMeshes = {};
        Mesh *pin1a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.625f, 0.150f, 2.650f)); pinMeshes.push_back(pin1a);
        Mesh *pin2a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.750f, 0.150f, 2.750f)); pinMeshes.push_back(pin2a);
        Mesh *pin3a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.750f, 0.150f, 2.550f)); pinMeshes.push_back(pin3a);
        Mesh *pin4a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.850f)); pinMeshes.push_back(pin4a);
        Mesh *pin5a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.650f)); pinMeshes.push_back(pin5a);
        Mesh *pin6a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.450f)); pinMeshes.push_back(pin6a);
        Mesh *pin7a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.950f)); pinMeshes.push_back(pin7a);
        Mesh *pin8a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.750f)); pinMeshes.push_back(pin8a);
        Mesh *pin9a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.550f)); pinMeshes.push_back(pin9a);
        Mesh *pin10a = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.350f)); pinMeshes.push_back(pin10a);

        Mesh *pin1b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.625f, 0.150f, 2.650f-ALLEY_SPACING*1)); pinMeshes.push_back(pin1b);
        Mesh *pin2b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.750f, 0.150f, 2.750f-ALLEY_SPACING*1)); pinMeshes.push_back(pin2b);
        Mesh *pin3b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.750f, 0.150f, 2.550f-ALLEY_SPACING*1)); pinMeshes.push_back(pin3b);
        Mesh *pin4b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.850f-ALLEY_SPACING*1)); pinMeshes.push_back(pin4b);
        Mesh *pin5b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.650f-ALLEY_SPACING*1)); pinMeshes.push_back(pin5b);
        Mesh *pin6b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.450f-ALLEY_SPACING*1)); pinMeshes.push_back(pin6b);
        Mesh *pin7b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.950f-ALLEY_SPACING*1)); pinMeshes.push_back(pin7b);
        Mesh *pin8b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.750f-ALLEY_SPACING*1)); pinMeshes.push_back(pin8b);
        Mesh *pin9b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.550f-ALLEY_SPACING*1)); pinMeshes.push_back(pin9b);
        Mesh *pin10b = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.350f-ALLEY_SPACING*1)); pinMeshes.push_back(pin10b);

        Mesh *pin1c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.625f, 0.150f, 2.650f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin1c);
        Mesh *pin2c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.750f, 0.150f, 2.750f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin2c);
        Mesh *pin3c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.750f, 0.150f, 2.550f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin3c);
        Mesh *pin4c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.850f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin4c);
        Mesh *pin5c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.650f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin5c);
        Mesh *pin6c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.450f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin6c);
        Mesh *pin7c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.950f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin7c);
        Mesh *pin8c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.750f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin8c);
        Mesh *pin9c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.550f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin9c);
        Mesh *pin10c = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.350f-ALLEY_SPACING*2+0.05f)); pinMeshes.push_back(pin10c);

        Mesh *pin1d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.625f, 0.150f, 2.650f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin1d);
        Mesh *pin2d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.750f, 0.150f, 2.750f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin2d);
        Mesh *pin3d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.750f, 0.150f, 2.550f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin3d);
        Mesh *pin4d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.850f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin4d);
        Mesh *pin5d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.650f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin5d);
        Mesh *pin6d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-12.875f, 0.150f, 2.450f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin6d);
        Mesh *pin7d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.950f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin7d);
        Mesh *pin8d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.750f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin8d);
        Mesh *pin9d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.550f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin9d);
        Mesh *pin10d = new ObjMesh("assets/models/custom/pin.obj", glm::vec3(-13.000f, 0.150f, 2.350f-ALLEY_SPACING*3+0.05f)); pinMeshes.push_back(pin10d);

        // init pins:
        const float scaleFactor = 0.45f;
        for (Mesh *pin : pinMeshes) {
            addToScene(pin);
            CollisionPin *collisionPin = new CollisionPin(glm::vec3(pin->position().x,pin->position().y+0.1f,pin->position().z), glm::vec3(0.0f), glm::vec3(scaleFactor), true);
            game->pins.push_back(collisionPin);
            pin->setParent(collisionPin);
            pin->position() = glm::vec3(0.0f, -0.1f, 0.0f);
            pin->scale() = glm::vec3(1/scaleFactor, 1/scaleFactor, 1/scaleFactor);
            addToScene(collisionPin);
        }

        // Player collision
        CollisionBox *collisionWall1 = new CollisionBox(glm::vec3(10.080f, -0.050f, 0.000f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.000f, 0.500f, 10.500f), true);
        addToScene(collisionWall1);
        CollisionBox *collisionWall2 = new CollisionBox(glm::vec3(1.580f, 2.550f, 0.000f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(28.500f, 0.500f, 10.500f), true);
        addToScene(collisionWall2);
        CollisionBox *collisionWall3 = new CollisionBox(glm::vec3(0.580f, 1.350f, 3.750f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(24.500f, 3.000f, 0.300f), true);
        addToScene(collisionWall3);
        CollisionBox *collisionWall4 = new CollisionBox(glm::vec3(0.580f, 1.350f, -3.750f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(24.500f, 3.000f, 0.300f) , true);
        addToScene(collisionWall4);
        CollisionBox *collisionWall5 = new CollisionBox(glm::vec3(12.630f, 1.350f, 0.430f), glm::vec3(0.000f, -1.571f, 0.000f), glm::vec3(9.250f, 3.000f, 0.300f), true);
        addToScene(collisionWall5);
        CollisionBox *collisionWall6 = new CollisionBox(glm::vec3(-13.250f, 1.350f, 0.430f), glm::vec3(0.000f, -1.571f, 0.000f), glm::vec3(9.250f, 3.000f, 0.300f), true);
        addToScene(collisionWall6);

        // Bowling Alley collisions
        std::vector<CollisionShape*> collisionShapes = {};
        CollisionBox *collisionBowlingAlley1 = new CollisionBox(glm::vec3(-3.670f, -0.050f, 2.630f-ALLEY_SPACING*0), glm::vec3(0.0f), glm::vec3(glm::vec3(20.500f, 0.500f, 0.750f)), true);
        addToScene(collisionBowlingAlley1); collisionShapes.push_back(collisionBowlingAlley1);
        CollisionBox *collisionBowlingAlley2 = new CollisionBox(glm::vec3(-3.670f, -0.050f, 2.630f-ALLEY_SPACING*1), glm::vec3(0.0f), glm::vec3(glm::vec3(20.500f, 0.500f, 0.750f)), true);
        addToScene(collisionBowlingAlley2); collisionShapes.push_back(collisionBowlingAlley2);
        CollisionBox *collisionBowlingAlley3 = new CollisionBox(glm::vec3(-3.670f, -0.050f, 2.630f-ALLEY_SPACING*2+0.05f), glm::vec3(0.0f), glm::vec3(glm::vec3(20.500f, 0.500f, 0.750f)), true);
        addToScene(collisionBowlingAlley3); collisionShapes.push_back(collisionBowlingAlley3);
        CollisionBox *collisionBowlingAlley4 = new CollisionBox(glm::vec3(-3.670f, -0.050f, 2.630f-ALLEY_SPACING*3+0.05f), glm::vec3(0.0f), glm::vec3(glm::vec3(20.500f, 0.500f, 0.750f)), true);
        addToScene(collisionBowlingAlley4); collisionShapes.push_back(collisionBowlingAlley4);

        CollisionBox *collisionBowlingAlleySeparation1 = new CollisionBox(glm::vec3(-5.970f, 0.350f, 3.550f), glm::vec3(0.0f), glm::vec3(glm::vec3(24.500f, 1.000f, 0.050f) ), true);
        addToScene(collisionBowlingAlleySeparation1); collisionShapes.push_back(collisionBowlingAlleySeparation1);
        CollisionBox *collisionBowlingAlleySeparation2 = new CollisionBox(glm::vec3(-5.970f, 0.350f, 1.750f), glm::vec3(0.0f), glm::vec3(glm::vec3(24.500f, 1.000f, 0.050f) ), true);
        addToScene(collisionBowlingAlleySeparation2); collisionShapes.push_back(collisionBowlingAlleySeparation2);
        CollisionBox *collisionBowlingAlleySeparation3 = new CollisionBox(glm::vec3(-5.970f, 0.350f, -0.040f), glm::vec3(0.0f), glm::vec3(glm::vec3(24.500f, 1.000f, 0.050f) ), true);
        addToScene(collisionBowlingAlleySeparation3); collisionShapes.push_back(collisionBowlingAlleySeparation3);
        CollisionBox *collisionBowlingAlleySeparation4 = new CollisionBox(glm::vec3(-5.970f, 0.350f, -1.820f), glm::vec3(0.0f), glm::vec3(glm::vec3(24.500f, 1.000f, 0.050f) ), true);
        addToScene(collisionBowlingAlleySeparation4); collisionShapes.push_back(collisionBowlingAlleySeparation4);
        CollisionBox *collisionBowlingAlleySeparation5 = new CollisionBox(glm::vec3(-5.970f, 0.350f, -3.600f), glm::vec3(0.0f), glm::vec3(glm::vec3(24.500f, 1.000f, 0.050f) ), true);
        addToScene(collisionBowlingAlleySeparation5); collisionShapes.push_back(collisionBowlingAlleySeparation5);

        CollisionBox *collsionFailSpot = new CollisionBox(glm::vec3(-2.920f, -0.180f, 0.000f), glm::vec3(0.000f, 0.000f, 0.000f), glm::vec3(19.000f, 0.500f, 10.500f), true);
        addToScene(collsionFailSpot); collisionShapes.push_back(collsionFailSpot);

        RigidSphere *bowlingBall = new RigidSphere(glm::vec3(0.0f, 1000.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)/4.0f, true);
        addToScene(bowlingBall); collisionShapes.push_back(bowlingBall);
        Mesh *bowlingBallMesh = new ObjMesh("assets/models/bowling/bowlingBall1.obj", true);
        addToScene(bowlingBallMesh);
        bowlingBallMesh->setParent(bowlingBall);
        bowlingBall->disable();
        game->bowlingBall = bowlingBall;

        //set physics material:
        for (CollisionShape *shape : collisionShapes) {
            shape->physicsMaterial.bounciness = 0.70f;
            shape->physicsMaterial.friction = 0.050f;
        }

        // screens
        Mesh *screen1 = new ObjMesh("assets/models/bowling/screen1.obj", glm::vec3(18.500f, 0.0f, 0.0f));
        addToScene(screen1);

        Mesh *screen2 = new ObjMesh("assets/models/bowling/screen2.obj", glm::vec3(18.490f, 0.0f, -0.05f));
        addToScene(screen2);

        Mesh *screen3 = new ObjMesh("assets/models/bowling/screen3.obj", glm::vec3(18.500f, 0.0f, 0.0f));
        addToScene(screen3);

        Mesh *screen4 = new ObjMesh("assets/models/bowling/screen4.obj", glm::vec3(18.500f, 0.0f, 0.0f));
        addToScene(screen4);

        // screen bg and videos
        ImageLabel *bg1 = new ImageLabel("assets/decals/background.jpg");
        bg1->position() = glm::vec3(6.70f, 1.5f, 2.640f); bg1->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        bg1->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(bg1);

        ImageLabel *bg2 = new ImageLabel("assets/decals/background.jpg");
        bg2->position() = glm::vec3(6.700f, 1.5f, 2.640f-ALLEY_SPACING); bg2->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        bg2->scale() = glm::vec3(0.930f, 0.590f, 1.0f)*0.94f; addToScene(bg2);

        ImageLabel *bg3 = new ImageLabel("assets/decals/background.jpg");
        bg3->position() = glm::vec3(6.700f, 1.5f, 2.640f-ALLEY_SPACING*2+0.05f); bg3->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        bg3->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(bg3);

        ImageLabel *bg4 = new ImageLabel("assets/decals/background.jpg");
        bg4->position() = glm::vec3(6.700f, 1.5f, 2.640f-ALLEY_SPACING*3+0.05f); bg4->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        bg4->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(bg4);


        TextLabel *scoreLabel1 = new TextLabel("assets/fonts/fredoka-one/fredokaone2.png");
        scoreLabel1->position() = glm::vec3(6.710f, 1.5f, 2.640f); scoreLabel1->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        scoreLabel1->scale() = glm::vec3(0.7835, 0.1105, 0.9); addToScene(scoreLabel1);
        scoreLabel1->setText("0 0|0 0|0 0|00");

        TextLabel *scoreLabel2 = new TextLabel("assets/fonts/fredoka-one/fredokaone2.png");
        scoreLabel2->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING); scoreLabel2->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        scoreLabel2->scale() = glm::vec3(0.7835, 0.1105, 0.9)*0.95f; addToScene(scoreLabel2);
        scoreLabel2->setText("0 0|0 0|0 0|00");

        TextLabel *scoreLabel3 = new TextLabel("assets/fonts/fredoka-one/fredokaone2.png");
        scoreLabel3->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING*2+0.05f); scoreLabel3->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        scoreLabel3->scale() = glm::vec3(0.7835, 0.1105, 0.9); addToScene(scoreLabel3);
        scoreLabel3->setText("0 0|0 0|0 0|00");

        TextLabel *scoreLabel4 = new TextLabel("assets/fonts/fredoka-one/fredokaone2.png");
        scoreLabel4->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING*3+0.05f); scoreLabel4->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        scoreLabel4->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(scoreLabel4);
        scoreLabel4->setText("0 0|0 0|0 0|00");

        ImageSequenceLabel *videoSplit1 = new ImageSequenceLabel("assets/decals/split1.png", 20, 20*8,16, 16);
        videoSplit1->position() = glm::vec3(6.710f, 1.5f, 2.640f); videoSplit1->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        videoSplit1->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(videoSplit1);

        ImageSequenceLabel *videoSpare2 = new ImageSequenceLabel("assets/decals/spare2.png", 20, 20*8,16, 16);
        videoSpare2->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING); videoSpare2->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        videoSpare2->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(videoSpare2);

        ImageSequenceLabel *videoStrike3 = new ImageSequenceLabel("assets/decals/strike3.png", 20, 20*8,16, 16);
        videoStrike3->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING*2+0.05f); videoStrike3->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        videoStrike3->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(videoStrike3);

        ImageSequenceLabel *videoMiss4 = new ImageSequenceLabel("assets/decals/miss4.png", 20, 20*6,12, 12);
        videoMiss4->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING*3+0.05f); videoMiss4->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        videoMiss4->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(videoMiss4);


        ImageSequenceLabel *videoIdle1 = new ImageSequenceLabel("assets/decals/tutorial.png", 8, 32*32,32, 32);
        videoIdle1->position() = glm::vec3(6.710f, 1.5f, 2.640f); videoIdle1->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        videoIdle1->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(videoIdle1);

        ImageSequenceLabel *videoIdle2 = new ImageSequenceLabel("assets/decals/tutorial.png", 8, 32*32,32, 32);
        videoIdle2->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING); videoIdle2->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        videoIdle2->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(videoIdle2); videoIdle2->setFrame(8*32);

        ImageSequenceLabel *videoIdle3 = new ImageSequenceLabel("assets/decals/tutorial.png", 8, 32*32,32, 32);
        videoIdle3->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING*2+0.05f); videoIdle3->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        videoIdle3->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(videoIdle3); videoIdle3->setFrame(16*32);

        ImageSequenceLabel *videoIdle4 = new ImageSequenceLabel("assets/decals/tutorial.png", 8, 32*32,32, 32);
        videoIdle4->position() = glm::vec3(6.710f, 1.5f, 2.640f-ALLEY_SPACING*3+0.05f); videoIdle4->rotation() = glm::vec3(0.0f, 1.571f, 0.0f);
        videoIdle4->scale() = glm::vec3(0.930f, 0.590f, 1.0f); addToScene(videoIdle4); videoIdle4->setFrame(24*32);


        game->scoreLabel1 = scoreLabel1; scoreLabel1->hide();
        game->scoreLabel2 = scoreLabel2; scoreLabel2->hide();
        game->scoreLabel3 = scoreLabel3; scoreLabel3->hide();
        game->scoreLabel4 = scoreLabel4; scoreLabel4->hide();

        game->videoSplit1 = videoSplit1; videoSplit1->hide();
        game->videoSpare2 = videoSpare2; videoSpare2->hide();
        game->videoStrike3 = videoStrike3; videoStrike3->hide();
        game->videoMiss4 = videoMiss4; videoMiss4->hide();

        game->videoIdle1 = videoIdle1;
        game->videoIdle2 = videoIdle2;
        game->videoIdle3 = videoIdle3;
        game->videoIdle4 = videoIdle4;


        // meshes loading from the bowling model
        Mesh *ballSideTrack1 = new ObjMesh("assets/models/bowling/ballSideTrack1.obj");
        addToScene(ballSideTrack1);

        Mesh *ballSideTrack10 = new ObjMesh("assets/models/bowling/ballSideTrack10.obj");
        addToScene(ballSideTrack10);

        Mesh *ballSideTrack11 = new ObjMesh("assets/models/bowling/ballSideTrack11.obj");
        addToScene(ballSideTrack11);

        Mesh *ballSideTrack2 = new ObjMesh("assets/models/bowling/ballSideTrack2.obj");
        addToScene(ballSideTrack2);

        Mesh *ballSideTrack3 = new ObjMesh("assets/models/bowling/ballSideTrack3.obj");
        addToScene(ballSideTrack3);

        Mesh *ballSideTrack4 = new ObjMesh("assets/models/bowling/ballSideTrack4.obj");
        addToScene(ballSideTrack4);

        Mesh *ballSideTrack5 = new ObjMesh("assets/models/bowling/ballSideTrack5.obj");
        addToScene(ballSideTrack5);

        Mesh *ballSideTrack6 = new ObjMesh("assets/models/bowling/ballSideTrack6.obj");
        addToScene(ballSideTrack6);

        Mesh *ballSideTrack7 = new ObjMesh("assets/models/bowling/ballSideTrack7.obj");
        addToScene(ballSideTrack7);

        Mesh *ballSideTrack8 = new ObjMesh("assets/models/bowling/ballSideTrack8.obj");
        addToScene(ballSideTrack8);

        Mesh *ballSideTrack9 = new ObjMesh("assets/models/bowling/ballSideTrack9.obj");
        addToScene(ballSideTrack9);

        Mesh *bin1 = new ObjMesh("assets/models/bowling/bin1.obj");
        addToScene(bin1);

        Mesh *bowlingAlley1 = new ObjMesh("assets/models/bowling/bowlingAlley1.obj");
        addToScene(bowlingAlley1);

        Mesh *bowlingAlleyFence1 = new ObjMesh("assets/models/bowling/bowlingAlleyFence1.obj");
        addToScene(bowlingAlleyFence1);

        Mesh *bowlingAlleyFloor1 = new ObjMesh("assets/models/bowling/bowlingAlleyFloor1.obj");
        addToScene(bowlingAlleyFloor1);

        Mesh *bowlingAlleyFloor2 = new ObjMesh("assets/models/bowling/bowlingAlleyFloor2.obj");
        addToScene(bowlingAlleyFloor2);

        Mesh *bowlingAlleyFloor3 = new ObjMesh("assets/models/bowling/bowlingAlleyFloor3.obj");
        addToScene(bowlingAlleyFloor3);

        Mesh *bowlingAlleyFloor4 = new ObjMesh("assets/models/bowling/bowlingAlleyFloor4.obj");
        addToScene(bowlingAlleyFloor4);

        Mesh *bowlingBall1 = new ObjMesh("assets/models/bowling/bowlingBall1.obj");
        addToScene(bowlingBall1); bowlingBallIds.push_back(bowlingBall1->getId());

        Mesh *bowlingBall10 = new ObjMesh("assets/models/bowling/bowlingBall10.obj");
        addToScene(bowlingBall10); bowlingBallIds.push_back(bowlingBall10->getId());

        Mesh *bowlingBall11 = new ObjMesh("assets/models/bowling/bowlingBall11.obj");
        addToScene(bowlingBall11); bowlingBallIds.push_back(bowlingBall11->getId());

        Mesh *bowlingBall12 = new ObjMesh("assets/models/bowling/bowlingBall12.obj");
        addToScene(bowlingBall12); bowlingBallIds.push_back(bowlingBall12->getId());

        Mesh *bowlingBall13 = new ObjMesh("assets/models/bowling/bowlingBall13.obj");
        addToScene(bowlingBall13); bowlingBallIds.push_back(bowlingBall13->getId());

        Mesh *bowlingBall14 = new ObjMesh("assets/models/bowling/bowlingBall14.obj");
        addToScene(bowlingBall14); bowlingBallIds.push_back(bowlingBall14->getId());

        Mesh *bowlingBall15 = new ObjMesh("assets/models/bowling/bowlingBall15.obj");
        addToScene(bowlingBall15); bowlingBallIds.push_back(bowlingBall15->getId());

        Mesh *bowlingBall16 = new ObjMesh("assets/models/bowling/bowlingBall16.obj");
        addToScene(bowlingBall16); bowlingBallIds.push_back(bowlingBall16->getId());

        Mesh *bowlingBall17 = new ObjMesh("assets/models/bowling/bowlingBall17.obj");
        addToScene(bowlingBall17); bowlingBallIds.push_back(bowlingBall17->getId());

        Mesh *bowlingBall18 = new ObjMesh("assets/models/bowling/bowlingBall18.obj");
        addToScene(bowlingBall18); bowlingBallIds.push_back(bowlingBall18->getId());

        Mesh *bowlingBall19 = new ObjMesh("assets/models/bowling/bowlingBall19.obj");
        addToScene(bowlingBall19); bowlingBallIds.push_back(bowlingBall19->getId());

        Mesh *bowlingBall2 = new ObjMesh("assets/models/bowling/bowlingBall2.obj");
        addToScene(bowlingBall2); bowlingBallIds.push_back(bowlingBall2->getId());

        Mesh *bowlingBall20 = new ObjMesh("assets/models/bowling/bowlingBall20.obj");
        addToScene(bowlingBall20); bowlingBallIds.push_back(bowlingBall20->getId());

        Mesh *bowlingBall21 = new ObjMesh("assets/models/bowling/bowlingBall21.obj");
        addToScene(bowlingBall21); bowlingBallIds.push_back(bowlingBall21->getId());

        Mesh *bowlingBall22 = new ObjMesh("assets/models/bowling/bowlingBall22.obj");
        addToScene(bowlingBall22); bowlingBallIds.push_back(bowlingBall22->getId());

        Mesh *bowlingBall23 = new ObjMesh("assets/models/bowling/bowlingBall23.obj");
        addToScene(bowlingBall23); bowlingBallIds.push_back(bowlingBall23->getId());

        Mesh *bowlingBall24 = new ObjMesh("assets/models/bowling/bowlingBall24.obj");
        addToScene(bowlingBall24); bowlingBallIds.push_back(bowlingBall24->getId());

        Mesh *bowlingBall25 = new ObjMesh("assets/models/bowling/bowlingBall25.obj");
        addToScene(bowlingBall25); bowlingBallIds.push_back(bowlingBall25->getId());

        Mesh *bowlingBall26 = new ObjMesh("assets/models/bowling/bowlingBall26.obj");
        addToScene(bowlingBall26); bowlingBallIds.push_back(bowlingBall26->getId());

        Mesh *bowlingBall27 = new ObjMesh("assets/models/bowling/bowlingBall27.obj");
        addToScene(bowlingBall27); bowlingBallIds.push_back(bowlingBall27->getId());

        Mesh *bowlingBall28 = new ObjMesh("assets/models/bowling/bowlingBall28.obj");
        addToScene(bowlingBall28); bowlingBallIds.push_back(bowlingBall28->getId());

        Mesh *bowlingBall29 = new ObjMesh("assets/models/bowling/bowlingBall29.obj");
        addToScene(bowlingBall29); bowlingBallIds.push_back(bowlingBall29->getId());

        Mesh *bowlingBall3 = new ObjMesh("assets/models/bowling/bowlingBall3.obj");
        addToScene(bowlingBall3); bowlingBallIds.push_back(bowlingBall3->getId());

        Mesh *bowlingBall30 = new ObjMesh("assets/models/bowling/bowlingBall30.obj");
        addToScene(bowlingBall30); bowlingBallIds.push_back(bowlingBall30->getId());

        Mesh *bowlingBall4 = new ObjMesh("assets/models/bowling/bowlingBall4.obj");
        addToScene(bowlingBall4); bowlingBallIds.push_back(bowlingBall4->getId());

        Mesh *bowlingBall5 = new ObjMesh("assets/models/bowling/bowlingBall5.obj");
        addToScene(bowlingBall5); bowlingBallIds.push_back(bowlingBall5->getId());

        Mesh *bowlingBall6 = new ObjMesh("assets/models/bowling/bowlingBall6.obj");
        addToScene(bowlingBall6); bowlingBallIds.push_back(bowlingBall6->getId());

        Mesh *bowlingBall7 = new ObjMesh("assets/models/bowling/bowlingBall7.obj");
        addToScene(bowlingBall7); bowlingBallIds.push_back(bowlingBall7->getId());

        Mesh *bowlingBall8 = new ObjMesh("assets/models/bowling/bowlingBall8.obj");
        addToScene(bowlingBall8); bowlingBallIds.push_back(bowlingBall8->getId());

        Mesh *bowlingBall9 = new ObjMesh("assets/models/bowling/bowlingBall9.obj");
        addToScene(bowlingBall9); bowlingBallIds.push_back(bowlingBall9->getId());

        Mesh *bowlingBallStand1 = new ObjMesh("assets/models/bowling/bowlingBallStand1.obj");
        addToScene(bowlingBallStand1);

        Mesh *bowlingBallStand2 = new ObjMesh("assets/models/bowling/bowlingBallStand2.obj");
        addToScene(bowlingBallStand2);

        Mesh *bowlingBallStand3 = new ObjMesh("assets/models/bowling/bowlingBallStand3.obj");
        addToScene(bowlingBallStand3);

        Mesh *buildingWalls1 = new ObjMesh("assets/models/bowling/buildingWalls1.obj");
        addToScene(buildingWalls1);

        Mesh *buildingWalls2 = new ObjMesh("assets/models/bowling/buildingWalls2.obj");
        addToScene(buildingWalls2);

        Mesh *buildingWalls3 = new ObjMesh("assets/models/bowling/buildingWalls3.obj");
        addToScene(buildingWalls3);

        Mesh *ceillingLights1 = new ObjMesh("assets/models/bowling/ceillingLights1.obj");
        addToScene(ceillingLights1);

        Mesh *chair1 = new ObjMesh("assets/models/bowling/chair1.obj");
        addToScene(chair1);

        Mesh *chair11 = new ObjMesh("assets/models/bowling/chair11.obj");
        addToScene(chair11);

        Mesh *chair12 = new ObjMesh("assets/models/bowling/chair12.obj");
        addToScene(chair12);

        Mesh *chair13 = new ObjMesh("assets/models/bowling/chair13.obj");
        addToScene(chair13);

        Mesh *chair14 = new ObjMesh("assets/models/bowling/chair14.obj");
        addToScene(chair14);

        Mesh *chair21 = new ObjMesh("assets/models/bowling/chair21.obj");
        addToScene(chair21);

        Mesh *chair22 = new ObjMesh("assets/models/bowling/chair22.obj");
        addToScene(chair22);

        Mesh *chair23 = new ObjMesh("assets/models/bowling/chair23.obj");
        addToScene(chair23);

        Mesh *chair24 = new ObjMesh("assets/models/bowling/chair24.obj");
        addToScene(chair24);

        Mesh *chair25 = new ObjMesh("assets/models/bowling/chair25.obj");
        addToScene(chair25);

        Mesh *chair26 = new ObjMesh("assets/models/bowling/chair26.obj");
        addToScene(chair26);

        Mesh *chair31 = new ObjMesh("assets/models/bowling/chair31.obj");
        addToScene(chair31);

        Mesh *chair32 = new ObjMesh("assets/models/bowling/chair32.obj");
        addToScene(chair32);

        Mesh *chair33 = new ObjMesh("assets/models/bowling/chair33.obj");
        addToScene(chair33);

        Mesh *chair34 = new ObjMesh("assets/models/bowling/chair34.obj");
        addToScene(chair34);

        Mesh *chair35 = new ObjMesh("assets/models/bowling/chair35.obj");
        addToScene(chair35);

        Mesh *chair41 = new ObjMesh("assets/models/bowling/chair41.obj");
        addToScene(chair41);

        Mesh *chair42 = new ObjMesh("assets/models/bowling/chair42.obj");
        addToScene(chair42);

        Mesh *chair43 = new ObjMesh("assets/models/bowling/chair43.obj");
        addToScene(chair43);

        Mesh *chair44 = new ObjMesh("assets/models/bowling/chair44.obj");
        addToScene(chair44);

        Mesh *chair45 = new ObjMesh("assets/models/bowling/chair45.obj");
        addToScene(chair45);

        Mesh *chair46 = new ObjMesh("assets/models/bowling/chair46.obj");
        addToScene(chair46);

        Mesh *chair51 = new ObjMesh("assets/models/bowling/chair51.obj");
        addToScene(chair51);

        Mesh *chair52 = new ObjMesh("assets/models/bowling/chair52.obj");
        addToScene(chair52);

        Mesh *chair53 = new ObjMesh("assets/models/bowling/chair53.obj");
        addToScene(chair53);

        Mesh *chair54 = new ObjMesh("assets/models/bowling/chair54.obj");
        addToScene(chair54);

        Mesh *chair55 = new ObjMesh("assets/models/bowling/chair55.obj");
        addToScene(chair55);

        Mesh *doorsWalls1d1 = new ObjMesh("assets/models/bowling/doorsWalls1d1.obj");
        addToScene(doorsWalls1d1);

        Mesh *doorsWalls2d1 = new ObjMesh("assets/models/bowling/doorsWalls2d1.obj", glm::vec3(0.0f, 0.0f, -0.05f));
        addToScene(doorsWalls2d1);

        Mesh *doorsWalls3d1 = new ObjMesh("assets/models/bowling/doorsWalls3d1.obj");
        addToScene(doorsWalls3d1);

        Mesh *doorsWalls4d1 = new ObjMesh("assets/models/bowling/doorsWalls4d1.obj");
        addToScene(doorsWalls4d1);

        Mesh *table1 = new ObjMesh("assets/models/bowling/table1.obj");
        addToScene(table1);

        Mesh *table2 = new ObjMesh("assets/models/bowling/table2.obj");
        addToScene(table2);

        Mesh *table3 = new ObjMesh("assets/models/bowling/table3.obj");
        addToScene(table3);

        Mesh *table4 = new ObjMesh("assets/models/bowling/table4.obj");
        addToScene(table4);

        Mesh *table5 = new ObjMesh("assets/models/bowling/table5.obj");
        addToScene(table5);

        Mesh *upscreen1 = new ObjMesh("assets/models/bowling/upscreen1.obj");
        addToScene(upscreen1);

        Mesh *upscreen2 = new ObjMesh("assets/models/bowling/upscreen2.obj");
        addToScene(upscreen2);

        Mesh *upscreen3 = new ObjMesh("assets/models/bowling/upscreen3.obj");
        addToScene(upscreen3);

        Mesh *upscreen4 = new ObjMesh("assets/models/bowling/upscreen4.obj");
        addToScene(upscreen4);

        Mesh *wall1 = new ObjMesh("assets/models/bowling/wall1.obj");
        addToScene(wall1);

        Mesh *wall2 = new ObjMesh("assets/models/bowling/wall2.obj");
        addToScene(wall2);

        Mesh *wall3 = new ObjMesh("assets/models/bowling/wall3.obj");
        addToScene(wall3);

        Mesh *wall4 = new ObjMesh("assets/models/bowling/wall4.obj");
        addToScene(wall4);

        Mesh *wall5 = new ObjMesh("assets/models/bowling/wall5.obj");
        addToScene(wall5);

        Mesh *windowFrames1 = new ObjMesh("assets/models/bowling/windowFrames1.obj");
        addToScene(windowFrames1);

        Mesh *windowFrames2 = new ObjMesh("assets/models/bowling/windowFrames2.obj");
        addToScene(windowFrames2);



        // set bowling game pointers
        game->door1 = doorsWalls1d1;
        game->door2 = doorsWalls2d1;
        game->door3 = doorsWalls3d1;
        game->door4 = doorsWalls4d1;
    }

    void BowlingScene::update(float deltaTime) {
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

        for (CollisionPin * pin : game->pins) {
            pin->updatePin(deltaTime, game->bowlingBall);
        }

        game->update(deltaTime);
    }

    void BowlingScene::physics_update(float deltaTime) {
        return;
    }

    void BowlingScene::onKeyboardEvent(unsigned char key, int x, int y, bool isDown) {
        if (inputController) {
            inputController->onKeyboardEvent(key, x, y, isDown);
        }
    }

    void BowlingScene::onMouseButtonEvent(int button, int state, int x, int y) {
        inputController->onMouseButtonEvent(button, state, x, y);
    }

    void BowlingScene::onMouseWheelEvent(int wheel, int direction, int x, int y) {
        if (inputController->getLevelEditor()->getEditMode() == EditMode::NONE) {
            if (direction > 0) {
                camera->addFov(-3.0f);
            } else {
                camera->addFov(3.0f);
            }
        }

        inputController->getLevelEditor()->onMouseWheelEvent(wheel, direction, x, y);
    }

    void BowlingScene::onMenuEvent(int option) {
        return;
    }
}