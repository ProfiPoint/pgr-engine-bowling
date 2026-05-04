#include <iostream>
#include <algorithm>
#include "pgr-portable.h"
#include "meshes/mesh.h"
#include "meshes/objMesh.h"
#include "meshes/textLabelMesh.h"
#include "geometry/camera.h"
#include "light/light.h"
#include "parser/input.h"
#include "shaders/shader.h"
#include "animation/spline.h"
#include "animation/catmullroll.h"
#include "animation/bezier.h"
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
    Input input = Input(camera, winWidth, winHeight);
    Skybox *skybox;

    std::vector<Spline *> splines = {};

    float updateTime() {
        int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
        uint64_t prevTime = time;
        time = currentFrameTime;
        return (currentFrameTime - prevTime) / 1000.0f; // delta time
    }

    void init() {
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
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

        glm::vec3 lightPosition = glm::vec3(-8.0f, 0.0f, 5.0f);
        glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 lightAmbient = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 lightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

        //Light *light = new SpotLight(lightPosition, lightDirection, lightAmbient, lightDiffuse, lightSpecular, 20.0f, 30.0f, 5.0f, false);
        //lights.push_back(light);
        Light *light1 = new PointLight(lightPosition, lightAmbient, lightDiffuse, lightSpecular, 50.0f, true);
        lights.push_back(light1);
        //Light *light2 = new DirectionalLight(-lightDirection, lightAmbient, lightDiffuse, lightSpecular);
        //lights.push_back(light2);

        //Light *light3 = new DirectionalLight(lightDirection, lightAmbient, lightDiffuse, lightSpecular);
        //lights.push_back(light3);

        //Mesh* triangleMesh = new Mesh();
        //meshes.push_back(triangleMesh);
        //Mesh *teddyMesh = new ObjMesh("meshes/models/teddy.obj", true);
        //teddyMesh->setMaterial(teddyMaterial);
        //meshes.push_back(teddyMesh);

        skybox = new Skybox(
            "assets/skybox/right.jpg",
            "assets/skybox/left.jpg",
            "assets/skybox/top.jpg",
            "assets/skybox/bottom.jpg",
            "assets/skybox/front.jpg",
            "assets/skybox/back.jpg",
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

        TextLabelMesh * textLabel1 = new TextLabelMesh("assets/fonts/fredoka-one/fredokaone2.png", teddyMaterial);
        textLabel1->scale() = glm::vec3(4.0f,1.0f,1.0f);
        textLabel1->position() = glm::vec3(0.0f, 0.0f, 0.0f);
        textLabel1->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
        textLabel1->setText("Hello World!");
        meshes.push_back(textLabel1);


        for (Mesh *mesh: meshes) {
            mesh->init(shaderPrg);
        }
        for (size_t i = 0; i < lights.size(); i++) {
            shader.setLight(lights[i], i);
        }

        std::vector<glm::vec3> camera_spline_points = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(5.0f, 2.0f, 5.0f),
            glm::vec3(10.0f, 0.0f, 10.0f),
            glm::vec3(15.0f, 5.0f, 0.0f),
            glm::vec3(7.0f, 13.0f, -5.0f),
            glm::vec3(10.0f, 100.0f, 10.0f),
        };

        Spline *camera_spline = new CatmullRoll(
            20.0f,
            camera_spline_points,
            camera.position(),
            [](glm::vec3 derivative) {
                if (glm::length(derivative) > 0.0001f) {  // prevent on screen glitching
                    camera.lookToPoint(camera.getPosition() + derivative);
                }
            }
        );

        splines.push_back(camera_spline);
        camera_spline->pause();
        input.setCameraSpline(camera_spline);


        Fog fog = Fog(15.0f, 40.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
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
            if (mesh->getMaterial()->getAlpha() < 1.0f) { continue; }
            if (dynamic_cast<const TextLabelMesh*>(mesh) != nullptr) { continue; }
            glStencilFunc(GL_ALWAYS, mesh->getId(), 0);
            shader.draw(*mesh, false); // drawing non-transparent objects
        }

        // Draw skybox
        glStencilFunc(GL_ALWAYS, 1, 0); // id = 1 is for skybox
        skybox->update(camera, winWidth, winHeight); // use skybox shader
        skybox->draw();

        // Draw Transparent Meshes
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE); // if the front triangle would render before the back it would fail

        shader.update(camera, winWidth, winHeight); // use main shader
        for (Mesh *mesh: meshes) {
            if (mesh->getMaterial()->getAlpha() == 1.0f) { continue; }
            glStencilFunc(GL_ALWAYS, mesh->getId(), 0);
            shader.draw(*mesh, true); // drawing transparent objects
        }

        meshes[3]->rotation().x += deltaTime;

        glDepthMask(GL_TRUE); // restore
        glDisable(GL_BLEND);


        if (!lights.empty()) {
            lights[0]->position() = camera.getPosition();
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
