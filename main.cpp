#include <iostream>
#include <algorithm>
#include "pgr-portable.h"
#include "meshes/mesh.h"
#include "meshes/objMesh.h"
#include "meshes/textLabel.h"
#include "meshes/imageSequenceLabel.h"
#include "geometry/camera.h"
#include "light/light.h"
#include "parser/input.h"
#include "shaders/shader.h"
#include "animation/spline.h"
#include "animation/catmullroll.h"
#include "animation/bezier.h"
#include "meshes/imageLabel.h"
#include "meshes/imageMoving.h"
#include "meshes/skybox.h"

namespace copakond {
    void menuCallback(int option);

    const char *WIN_TITLE = "PGR Semestral Work Copakond";
    int winWidth = 1280;
    int winHeight = 720;

    // shared variables
    uint64_t time = 0;
    std::vector<Mesh *> meshes = {};
    std::vector<Light *> lights = {};
    Shader shader = Shader();
    Camera camera(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        1000.0f
    );
    Light *sun;
    Input input = Input(camera, winWidth, winHeight);
    Skybox *skybox;

    std::vector<Spline *> splines = {};

    ImageLabel *clockHandHour;
    ImageLabel *clockHandMin;
    ImageLabel *clockHandSec;

    //float clockTime[] = {03,58,30}; // hh:mm:ss
    float clockTime[] = {0,0,0}; // hh:mm:ss

    float updateTime() {
        int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
        uint64_t prevTime = time;
        time = currentFrameTime;
        return (currentFrameTime - prevTime) / 1000.0f; // delta time
    }

    void init() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

        GLuint shaderPrg = shader.init(
            "shaders/shaders/shader.vert",
            "shaders/shaders/shader.frag"
        );

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
        //lights.push_back(light);
        //Light *light1 = new PointLight(lightPosition, lightAmbient, lightDiffuse, lightSpecular, 50.0f, true);
        //lights.push_back(light1);
        sun = new DirectionalLight(-lightDirection, lightAmbient, lightDiffuse, lightSpecular);
        lights.push_back(sun);

        //Light *light3 = new DirectionalLight(lightDirection, lightAmbient, lightDiffuse, lightSpecular);
        //lights.push_back(light3);

        //Mesh* triangleMesh = new Mesh();
        //meshes.push_back(triangleMesh);
        //Mesh *teddyMesh = new ObjMesh("meshes/models/teddy.obj", true);
        //teddyMesh->setMaterial(teddyMaterial);
        //meshes.push_back(teddyMesh);

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
        meshes.push_back(oldShipMesh);

        Mesh *shipMesh = new ObjMesh("assets/models/ship2.obj", false, glm::vec3(-5.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, glm::pi<float>(), 0.0f), glm::vec3(0.125f, 0.125f, 0.125f));
        meshes.push_back(shipMesh);

        Mesh *bodyMesh = new ObjMesh("assets/models/characters/character-a.obj", false, glm::vec3(0.0f, -1.0f, 0.0f),
                                       glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        meshes.push_back(bodyMesh);

        Mesh *body2Mesh = new ObjMesh("assets/models/characters/character-f.obj", false, glm::vec3(2.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        meshes.push_back(body2Mesh);

        body2Mesh->setParent(bodyMesh);

        TextLabel *textLabel1 = new TextLabel("assets/fonts/fredoka-one/fredokaone2.png", labelMaterial);
        textLabel1->scale() = glm::vec3(6.0f,1.0f,1.0f);
        textLabel1->position() = glm::vec3(0.0f, 6.0f, 0.0f);
        textLabel1->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
        textLabel1->setText("Hello World!");
        meshes.push_back(textLabel1);

        TextLabel *textLabel2 = new TextLabel("assets/fonts/fredoka-one/fredokaone2.png");
        textLabel2->scale() = glm::vec3(50.0f,1.0f,1.0f);
        textLabel2->position() = glm::vec3(0.0f, 10.0f, 0.0f);
        textLabel2->setColor(glm::vec3(1.0f, 0.5f, 0.0f));
        textLabel2->setText("copakond Presents super fun project :D 3257 &*@!#$ 131 13 13a1 d3a1wda51d65aww11d65a1d");
        meshes.push_back(textLabel2);

        ImageSequenceLabel *imageSequenceLabel = new ImageSequenceLabel("assets/decals/cara_mia_portal2.jpg", 20, 40*40, 40, 40);
        imageSequenceLabel->position() = glm::vec3(0.0f, 0.0f, -20.0f);
        imageSequenceLabel->scale() = glm::vec3(16*2.0f,9*2.0f,1.0f);
        meshes.push_back(imageSequenceLabel);

        ImageMoving *imageMoving = new ImageMoving("assets/decals/arrow2.png", glm::vec2(0.0f, -1.0f), glm::vec2(1.0f, 8.0f));
        imageMoving->position() = glm::vec3(0.0f, 0.0f, -14.0f);
        imageMoving->scale() = glm::vec3(3.0f, 3*8.0f,1.0f);
        meshes.push_back(imageMoving);


        // clocks
        ImageLabel *clock = new ImageLabel("assets/decals/clock.png");
        clock->position() = glm::vec3(0.0f, 6.0f, 0.1f);
        clock->scale() = glm::vec3(3.0f,3.0f,3.0f);
        meshes.push_back(clock);

        clockHandSec = new ImageLabel("assets/decals/handSeconds2.png");
        clockHandSec->position() = glm::vec3(0.0f, 0.0f, 0.005f);
        clockHandSec->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
        clockHandSec->setParent(clock);
        meshes.push_back(clockHandSec);

        clockHandMin = new ImageLabel("assets/decals/handMinutes2.png");
        clockHandMin->position() = glm::vec3(0.0f, 0.0f, 0.01f);
        clockHandMin->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
        clockHandMin->setParent(clock);
        meshes.push_back(clockHandMin);

        clockHandHour = new ImageLabel("assets/decals/handHours2.png");
        clockHandHour->position() = glm::vec3(0.0f, 0.0f, 0.01f);
        clockHandHour->scale() = glm::vec3(1.0f*0.05f, 1.0f, 1.0f*0.05f);
        clockHandHour->setParent(clock);
        meshes.push_back(clockHandHour);

        for (Mesh *mesh: meshes) {
            mesh->init(shaderPrg);
        }
        for (size_t i = 0; i < lights.size(); i++) {
            shader.setLight(lights[i], i);
        }

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
            camera.position(),
            [](glm::vec3 derivative) {
                if (glm::length(derivative) > 0.0001f) {  // prevent on screen glitching
                    camera.lookToPoint(camera.getPosition() + derivative);
                }
            }
        );

        splines.push_back(cameraSpline);
        cameraSpline->pause();
        input.setCameraSpline(cameraSpline);


        Fog fog = Fog(30.0f, 50.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        camera.setFog(fog);


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glCullFace( GL_BACK);
        glEnable(GL_CULL_FACE);

        // enable stencil test for mouse clicking
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        glutCreateMenu(menuCallback);
        glutAddMenuEntry("Player Cam", 1);
        glutAddMenuEntry("Catmull Roll Cam", 2);
        glutAddMenuEntry("Static Cam 1", 3);
        glutAddMenuEntry("Static Cam 2", 4);
        glutAddMenuEntry("Full Screen", 5);
        glutAddMenuEntry("Exit Game", 6);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }

    void draw() {
        float deltaTime = updateTime(); // calculate delta time
        input.keyInput(deltaTime); // process input

        // update spline animations
        for (Spline *spline: splines) {
            spline->update(deltaTime);
        }


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
        float skyboxBlending = 0.0f; // default day

        if (currentHour >= 20.0f || currentHour <= 4.0f) { skyboxBlending = 1.0f; } // full night
        else if (currentHour > 4.0f && currentHour < 8.0f) { skyboxBlending = 1.0f - ((currentHour - 4.0f) / 4.0f); } // night -> day
        else if (currentHour > 16.0f && currentHour < 20.0f) { skyboxBlending = (currentHour - 16.0f) / 4.0f; } // day -> night

        // update sunlight based of the time
        // z stars at -1, middle 0, end 1 (pi/2, pi, 3pi/2)
        // y stars at 0, middle 1, end 0 (pi/2, pi, 3pi/2)
        float thetaSun = (2 * glm::pi<float>() * currentHour / 24.0f); // 0 is down, 12 is up, 24 down, 6 start, 18 end
        sun->diffuse() = glm::vec3(0.5f, 0.5f, 0.5f) * (1-skyboxBlending); // set the intensity
        sun->direction() = glm::vec3(0.0f, glm::cos(thetaSun), glm::sin(thetaSun));





        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // sort all meshes, from the furthest to the nearest (for transparent meshes), all meshes, could be optimized more...
        glm::vec3 camPos = camera.getPosition();
        std::sort(meshes.begin(), meshes.end(), [&camPos](Mesh* a, Mesh* b) {
                glm::vec3 pos1 = glm::vec3(a->getModelMatrix()[3]); // position
                glm::vec3 pos2 = glm::vec3(b->getModelMatrix()[3]); // position

                return glm::distance(camPos, pos1) > glm::distance(camPos, pos2);
        });

        // Draw Non-transparent Meshes
        shader.update(camera, winWidth, winHeight); // use main shader
        for (Mesh *mesh: meshes) {
            if (mesh->getMaterial()->getAlpha() <= 0.999f) { continue; }
            if (dynamic_cast<const TextLabel*>(mesh) != nullptr) { continue; }
            glStencilFunc(GL_ALWAYS, mesh->getId(), 0);
            shader.draw(*mesh, false, deltaTime); // drawing non-transparent objects
        }

        // Draw skybox
        glStencilFunc(GL_ALWAYS, 1, 0); // id = 1 is for skybox
        skybox->update(camera, winWidth, winHeight, deltaTime, skyboxBlending); // use skybox shader
        skybox->draw(deltaTime);

        // Draw Transparent Meshes
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE); // if the front triangle would render before the back it would fail

        shader.update(camera, winWidth, winHeight); // use main shader
        for (Mesh *mesh: meshes) {
            if (mesh->getMaterial()->getAlpha() > 0.9999f) { continue; }
            glStencilFunc(GL_ALWAYS, mesh->getId(), 0);
            shader.draw(*mesh, true, deltaTime); // drawing transparent objects
        }

        //meshes[3]->rotation().x += deltaTime;

        glDepthMask(GL_TRUE); // restore
        glDisable(GL_BLEND);


        if (!lights.empty()) {
            //lights[0]->position() = camera.getPosition();
            shader.updateLight(lights[0]);
        }

        glutSwapBuffers(); // swap front and back screen buffer
        glutPostRedisplay(); // !!!!!!!!! schedules display, doesnt stack!!!
    }

    // TODO take the logic away from the input into different class
    void menuCallback(int option) {
        if (option == 1) {
            input._canMove = true;
            input._spline->pause();
        }

        if (option == 2) {
            input._canMove = false;
            input._spline->reset();
            input._spline->unpause();
        }

        if (option == 3) {
            input._canMove = false;
            input._spline->pause();
            input._camera.position() = glm::vec3(5.0f, 0.0f, 20.0f);
            input._camera.lookToPoint(glm::vec3(0.0f, 0.0f, 0.0f));
        }

        if (option == 4) {
            input._canMove = false;
            input._spline->pause();
            input._camera.position() = glm::vec3(5.0f, 0.0f, -20.0f);
            input._camera.lookToPoint(glm::vec3(0.0f, 0.0f, 0.0f));
        }

        if (option == 5) {
            if (input._isFullScreen) {
                glutReshapeWindow(input._windowWidth, input._windowHeight);
                glutPositionWindow(input._windowPosX, input._windowPosY);
                input._isFullScreen = false;
            } else {
                input._windowWidth = glutGet(GLUT_WINDOW_WIDTH);
                input._windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
                input._windowPosX = glutGet(GLUT_WINDOW_X);
                input._windowPosY = glutGet(GLUT_WINDOW_Y);

                glutFullScreen();
                input._isFullScreen = true;
            }
        }

        if (option == 6) {
            glutLeaveMainLoop();
        }

        input.resetMouseTarget();
    }

    void handleMouseClickedOnObject(int id) {
        std::cout << "Clicked on object: " << id << std::endl;
    }

    void keyboardInputEvent(unsigned char key, int x, int y) {
        input.keyboardInputEvent(key, x, y);
    }

    void specKeyboardInputEvent(int key, int x, int y) {
        input.specKeyboardInputEvent(key, x, y);
    }

    void keyboardUpInputEvent(unsigned char key, int x, int y) {
        input.keyboardUpInputEvent(key, x, y);
    }

    void specKeyboardUpInputEvent(int key, int x, int y) {
        input.specKeyboardUpInputEvent(key, x, y);
    }

    void mouseButtonEvent(int button, int state, int x, int y) {
        int objectClickedId = (int)input.mouseButtonEvent(button, state, x, y);
        if (objectClickedId > 0) { handleMouseClickedOnObject(objectClickedId); }
    }

    void mouseMoveEvent(int x, int y) {
        input.mouseMoveEvent(x, y);
    }

    void mouseWheelEvent(int wheel, int direction, int x, int y) {
        input.mouseWheelEvent(wheel, direction, x, y);
    }

    void screenResizeEvent(int width, int height) {
        if (width == 0) width = 1; // sadly it can be 0 for some reason.
        if (height == 0) height = 1;

        winWidth = width;
        winHeight = height;

        glViewport(0, 0, width, height);
        input.update(winWidth, winHeight);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(copakond::winWidth, copakond::winHeight);
    glutCreateWindow(copakond::WIN_TITLE);

    // INPUT - keyboard and mouse event callbacks
    glutKeyboardFunc(copakond::keyboardInputEvent);
    glutSpecialFunc(copakond::specKeyboardInputEvent);
    glutKeyboardUpFunc(copakond::keyboardUpInputEvent);
    glutSpecialUpFunc(copakond::specKeyboardUpInputEvent);

    glutMouseFunc(copakond::mouseButtonEvent);
    glutPassiveMotionFunc(copakond::mouseMoveEvent);
    glutMotionFunc(copakond::mouseMoveEvent);
    glutMouseWheelFunc(copakond::mouseWheelEvent);
    glutSetCursor(GLUT_CURSOR_NONE); // hide cursor

    // SET DRAW CALLBACK
    glutDisplayFunc(copakond::draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) {
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");
    }

    copakond::init();

    glutMainLoop();
    return 0;
}
