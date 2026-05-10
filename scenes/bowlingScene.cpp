#include "bowlingScene.h"

namespace copakond {
    BowlingScene::BowlingScene(const char *sceneName, Input* input, Shader* shader, int winWidth, int winHeight): Scene(sceneName, input, shader, winWidth, winHeight) {
        camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 1000.0f);
    }

    BowlingScene::~BowlingScene() {};

    void BowlingScene::init() {
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

        
        //Mesh *bomb = new ObjMesh("assets/models/custom/bomb.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
         //   glm::vec3(1.0f, 1.0f, 1.0f));
        //addToScene(bomb);

        Mesh *bomb = new ObjMesh("assets/models/custom/crate.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bomb);

        
        // meshes loading from the bowling model
        Mesh *ballSideTrack1 = new ObjMesh("assets/models/bowling/ballSideTrack1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack1);

        Mesh *ballSideTrack10 = new ObjMesh("assets/models/bowling/ballSideTrack10.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack10);

        Mesh *ballSideTrack11 = new ObjMesh("assets/models/bowling/ballSideTrack11.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack11);

        Mesh *ballSideTrack2 = new ObjMesh("assets/models/bowling/ballSideTrack2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack2);

        Mesh *ballSideTrack3 = new ObjMesh("assets/models/bowling/ballSideTrack3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack3);

        Mesh *ballSideTrack4 = new ObjMesh("assets/models/bowling/ballSideTrack4.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack4);

        Mesh *ballSideTrack5 = new ObjMesh("assets/models/bowling/ballSideTrack5.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack5);

        Mesh *ballSideTrack6 = new ObjMesh("assets/models/bowling/ballSideTrack6.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack6);

        Mesh *ballSideTrack7 = new ObjMesh("assets/models/bowling/ballSideTrack7.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack7);

        Mesh *ballSideTrack8 = new ObjMesh("assets/models/bowling/ballSideTrack8.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack8);

        Mesh *ballSideTrack9 = new ObjMesh("assets/models/bowling/ballSideTrack9.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ballSideTrack9);

        Mesh *bin1 = new ObjMesh("assets/models/bowling/bin1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bin1);

        Mesh *bowlingAlley1 = new ObjMesh("assets/models/bowling/bowlingAlley1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingAlley1);

        Mesh *bowlingAlleyFence1 = new ObjMesh("assets/models/bowling/bowlingAlleyFence1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingAlleyFence1);

        Mesh *bowlingAlleyFloor1 = new ObjMesh("assets/models/bowling/bowlingAlleyFloor1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingAlleyFloor1);

        Mesh *bowlingAlleyFloor2 = new ObjMesh("assets/models/bowling/bowlingAlleyFloor2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingAlleyFloor2);

        Mesh *bowlingAlleyFloor3 = new ObjMesh("assets/models/bowling/bowlingAlleyFloor3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingAlleyFloor3);

        Mesh *bowlingAlleyFloor4 = new ObjMesh("assets/models/bowling/bowlingAlleyFloor4.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingAlleyFloor4);

        Mesh *bowlingBall1 = new ObjMesh("assets/models/bowling/bowlingBall1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall1);

        Mesh *bowlingBall10 = new ObjMesh("assets/models/bowling/bowlingBall10.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall10);

        Mesh *bowlingBall11 = new ObjMesh("assets/models/bowling/bowlingBall11.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall11);

        Mesh *bowlingBall12 = new ObjMesh("assets/models/bowling/bowlingBall12.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall12);

        Mesh *bowlingBall13 = new ObjMesh("assets/models/bowling/bowlingBall13.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall13);

        Mesh *bowlingBall14 = new ObjMesh("assets/models/bowling/bowlingBall14.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall14);

        Mesh *bowlingBall15 = new ObjMesh("assets/models/bowling/bowlingBall15.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall15);

        Mesh *bowlingBall16 = new ObjMesh("assets/models/bowling/bowlingBall16.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall16);

        Mesh *bowlingBall17 = new ObjMesh("assets/models/bowling/bowlingBall17.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall17);

        Mesh *bowlingBall18 = new ObjMesh("assets/models/bowling/bowlingBall18.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall18);

        Mesh *bowlingBall19 = new ObjMesh("assets/models/bowling/bowlingBall19.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall19);

        Mesh *bowlingBall2 = new ObjMesh("assets/models/bowling/bowlingBall2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall2);

        Mesh *bowlingBall20 = new ObjMesh("assets/models/bowling/bowlingBall20.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall20);

        Mesh *bowlingBall21 = new ObjMesh("assets/models/bowling/bowlingBall21.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall21);

        Mesh *bowlingBall22 = new ObjMesh("assets/models/bowling/bowlingBall22.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall22);

        Mesh *bowlingBall23 = new ObjMesh("assets/models/bowling/bowlingBall23.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall23);

        Mesh *bowlingBall24 = new ObjMesh("assets/models/bowling/bowlingBall24.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall24);

        Mesh *bowlingBall25 = new ObjMesh("assets/models/bowling/bowlingBall25.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall25);

        Mesh *bowlingBall26 = new ObjMesh("assets/models/bowling/bowlingBall26.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall26);

        Mesh *bowlingBall27 = new ObjMesh("assets/models/bowling/bowlingBall27.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall27);

        Mesh *bowlingBall28 = new ObjMesh("assets/models/bowling/bowlingBall28.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall28);

        Mesh *bowlingBall29 = new ObjMesh("assets/models/bowling/bowlingBall29.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall29);

        Mesh *bowlingBall3 = new ObjMesh("assets/models/bowling/bowlingBall3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall3);

        Mesh *bowlingBall30 = new ObjMesh("assets/models/bowling/bowlingBall30.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall30);

        Mesh *bowlingBall4 = new ObjMesh("assets/models/bowling/bowlingBall4.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall4);

        Mesh *bowlingBall5 = new ObjMesh("assets/models/bowling/bowlingBall5.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall5);

        Mesh *bowlingBall6 = new ObjMesh("assets/models/bowling/bowlingBall6.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall6);

        Mesh *bowlingBall7 = new ObjMesh("assets/models/bowling/bowlingBall7.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall7);

        Mesh *bowlingBall8 = new ObjMesh("assets/models/bowling/bowlingBall8.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall8);

        Mesh *bowlingBall9 = new ObjMesh("assets/models/bowling/bowlingBall9.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBall9);

        Mesh *bowlingBallStand1 = new ObjMesh("assets/models/bowling/bowlingBallStand1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBallStand1);

        Mesh *bowlingBallStand2 = new ObjMesh("assets/models/bowling/bowlingBallStand2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBallStand2);

        Mesh *bowlingBallStand3 = new ObjMesh("assets/models/bowling/bowlingBallStand3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(bowlingBallStand3);

        Mesh *buildingWalls1 = new ObjMesh("assets/models/bowling/buildingWalls1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(buildingWalls1);

        Mesh *buildingWalls2 = new ObjMesh("assets/models/bowling/buildingWalls2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(buildingWalls2);

        Mesh *buildingWalls3 = new ObjMesh("assets/models/bowling/buildingWalls3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(buildingWalls3);

        Mesh *ceillingLights1 = new ObjMesh("assets/models/bowling/ceillingLights1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(ceillingLights1);

        Mesh *chair1 = new ObjMesh("assets/models/bowling/chair1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair1);

        Mesh *chair11 = new ObjMesh("assets/models/bowling/chair11.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair11);

        Mesh *chair12 = new ObjMesh("assets/models/bowling/chair12.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair12);

        Mesh *chair13 = new ObjMesh("assets/models/bowling/chair13.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair13);

        Mesh *chair14 = new ObjMesh("assets/models/bowling/chair14.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair14);

        Mesh *chair21 = new ObjMesh("assets/models/bowling/chair21.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair21);

        Mesh *chair22 = new ObjMesh("assets/models/bowling/chair22.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair22);

        Mesh *chair23 = new ObjMesh("assets/models/bowling/chair23.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair23);

        Mesh *chair24 = new ObjMesh("assets/models/bowling/chair24.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair24);

        Mesh *chair25 = new ObjMesh("assets/models/bowling/chair25.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair25);

        Mesh *chair26 = new ObjMesh("assets/models/bowling/chair26.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair26);

        Mesh *chair31 = new ObjMesh("assets/models/bowling/chair31.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair31);

        Mesh *chair32 = new ObjMesh("assets/models/bowling/chair32.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair32);

        Mesh *chair33 = new ObjMesh("assets/models/bowling/chair33.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair33);

        Mesh *chair34 = new ObjMesh("assets/models/bowling/chair34.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair34);

        Mesh *chair35 = new ObjMesh("assets/models/bowling/chair35.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair35);

        Mesh *chair41 = new ObjMesh("assets/models/bowling/chair41.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair41);

        Mesh *chair42 = new ObjMesh("assets/models/bowling/chair42.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair42);

        Mesh *chair43 = new ObjMesh("assets/models/bowling/chair43.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair43);

        Mesh *chair44 = new ObjMesh("assets/models/bowling/chair44.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair44);

        Mesh *chair45 = new ObjMesh("assets/models/bowling/chair45.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair45);

        Mesh *chair46 = new ObjMesh("assets/models/bowling/chair46.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair46);

        Mesh *chair51 = new ObjMesh("assets/models/bowling/chair51.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair51);

        Mesh *chair52 = new ObjMesh("assets/models/bowling/chair52.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair52);

        Mesh *chair53 = new ObjMesh("assets/models/bowling/chair53.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair53);

        Mesh *chair54 = new ObjMesh("assets/models/bowling/chair54.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair54);

        Mesh *chair55 = new ObjMesh("assets/models/bowling/chair55.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(chair55);

        Mesh *doorsWalls1d1 = new ObjMesh("assets/models/bowling/doorsWalls1d1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(doorsWalls1d1);

        Mesh *doorsWalls2d1 = new ObjMesh("assets/models/bowling/doorsWalls2d1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(doorsWalls2d1);

        Mesh *doorsWalls3d1 = new ObjMesh("assets/models/bowling/doorsWalls3d1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(doorsWalls3d1);

        Mesh *doorsWalls4d1 = new ObjMesh("assets/models/bowling/doorsWalls4d1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(doorsWalls4d1);

        Mesh *screen1 = new ObjMesh("assets/models/bowling/screen1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(screen1);

        Mesh *screen2 = new ObjMesh("assets/models/bowling/screen2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(screen2);

        Mesh *screen3 = new ObjMesh("assets/models/bowling/screen3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(screen3);

        Mesh *screen4 = new ObjMesh("assets/models/bowling/screen4.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(screen4);

        Mesh *table1 = new ObjMesh("assets/models/bowling/table1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(table1);

        Mesh *table2 = new ObjMesh("assets/models/bowling/table2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(table2);

        Mesh *table3 = new ObjMesh("assets/models/bowling/table3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(table3);

        Mesh *table4 = new ObjMesh("assets/models/bowling/table4.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(table4);

        Mesh *table5 = new ObjMesh("assets/models/bowling/table5.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(table5);

        Mesh *teapot1 = new ObjMesh("assets/models/bowling/teapot1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot1);

        Mesh *teapot10 = new ObjMesh("assets/models/bowling/teapot10.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot10);

        Mesh *teapot11 = new ObjMesh("assets/models/bowling/teapot11.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot11);

        Mesh *teapot12 = new ObjMesh("assets/models/bowling/teapot12.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot12);

        Mesh *teapot13 = new ObjMesh("assets/models/bowling/teapot13.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot13);

        Mesh *teapot14 = new ObjMesh("assets/models/bowling/teapot14.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot14);

        Mesh *teapot15 = new ObjMesh("assets/models/bowling/teapot15.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot15);

        Mesh *teapot16 = new ObjMesh("assets/models/bowling/teapot16.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot16);

        Mesh *teapot17 = new ObjMesh("assets/models/bowling/teapot17.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot17);

        Mesh *teapot18 = new ObjMesh("assets/models/bowling/teapot18.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot18);

        Mesh *teapot19 = new ObjMesh("assets/models/bowling/teapot19.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot19);

        Mesh *teapot2 = new ObjMesh("assets/models/bowling/teapot2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot2);

        Mesh *teapot20 = new ObjMesh("assets/models/bowling/teapot20.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot20);

        Mesh *teapot21 = new ObjMesh("assets/models/bowling/teapot21.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot21);

        Mesh *teapot22 = new ObjMesh("assets/models/bowling/teapot22.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot22);

        Mesh *teapot23 = new ObjMesh("assets/models/bowling/teapot23.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot23);

        Mesh *teapot24 = new ObjMesh("assets/models/bowling/teapot24.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot24);

        Mesh *teapot25 = new ObjMesh("assets/models/bowling/teapot25.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot25);

        Mesh *teapot26 = new ObjMesh("assets/models/bowling/teapot26.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot26);

        Mesh *teapot27 = new ObjMesh("assets/models/bowling/teapot27.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot27);

        Mesh *teapot28 = new ObjMesh("assets/models/bowling/teapot28.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot28);

        Mesh *teapot29 = new ObjMesh("assets/models/bowling/teapot29.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot29);

        Mesh *teapot3 = new ObjMesh("assets/models/bowling/teapot3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot3);

        Mesh *teapot30 = new ObjMesh("assets/models/bowling/teapot30.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot30);

        Mesh *teapot31 = new ObjMesh("assets/models/bowling/teapot31.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot31);

        Mesh *teapot32 = new ObjMesh("assets/models/bowling/teapot32.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot32);

        Mesh *teapot33 = new ObjMesh("assets/models/bowling/teapot33.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot33);

        Mesh *teapot34 = new ObjMesh("assets/models/bowling/teapot34.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot34);

        Mesh *teapot35 = new ObjMesh("assets/models/bowling/teapot35.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot35);

        Mesh *teapot36 = new ObjMesh("assets/models/bowling/teapot36.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot36);

        Mesh *teapot37 = new ObjMesh("assets/models/bowling/teapot37.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot37);

        Mesh *teapot38 = new ObjMesh("assets/models/bowling/teapot38.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot38);

        Mesh *teapot39 = new ObjMesh("assets/models/bowling/teapot39.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot39);

        Mesh *teapot4 = new ObjMesh("assets/models/bowling/teapot4.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot4);

        Mesh *teapot40 = new ObjMesh("assets/models/bowling/teapot40.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot40);

        Mesh *teapot5 = new ObjMesh("assets/models/bowling/teapot5.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot5);

        Mesh *teapot6 = new ObjMesh("assets/models/bowling/teapot6.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot6);

        Mesh *teapot7 = new ObjMesh("assets/models/bowling/teapot7.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot7);

        Mesh *teapot8 = new ObjMesh("assets/models/bowling/teapot8.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot8);

        Mesh *teapot9 = new ObjMesh("assets/models/bowling/teapot9.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(teapot9);

        Mesh *upscreen1 = new ObjMesh("assets/models/bowling/upscreen1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(upscreen1);

        Mesh *upscreen2 = new ObjMesh("assets/models/bowling/upscreen2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(upscreen2);

        Mesh *upscreen3 = new ObjMesh("assets/models/bowling/upscreen3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(upscreen3);

        Mesh *upscreen4 = new ObjMesh("assets/models/bowling/upscreen4.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(upscreen4);

        Mesh *wall1 = new ObjMesh("assets/models/bowling/wall1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(wall1);

        Mesh *wall2 = new ObjMesh("assets/models/bowling/wall2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(wall2);

        Mesh *wall3 = new ObjMesh("assets/models/bowling/wall3.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(wall3);

        Mesh *wall4 = new ObjMesh("assets/models/bowling/wall4.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(wall4);

        Mesh *wall5 = new ObjMesh("assets/models/bowling/wall5.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(wall5);

        Mesh *windowFrames1 = new ObjMesh("assets/models/bowling/windowFrames1.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(windowFrames1);

        Mesh *windowFrames2 = new ObjMesh("assets/models/bowling/windowFrames2.obj", false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        addToScene(windowFrames2);


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